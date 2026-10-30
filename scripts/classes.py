#!/usr/bin/env python3
"""MSVC x86 RTTI class analysis: hierarchy, vtables, who writes the vptr.

Everything here is derived from the binary alone (no map/pdb):

  * RTTI: COL -> TypeDescriptor name, ClassHierarchyDescriptor -> direct bases,
    vtable slot lists (primary and secondary).
  * vptr stores: every `mov [reg+disp], imm32` / `mov reg, imm32` whose immediate is a
    vtable address marks the containing function as a constructor or destructor of
    that class (or as the deleting-destructor wrapper).
  * deleting-destructor wrapper (vtable slot 0, `test byte [esp+8],1`): the call just
    before that test is the real destructor.
  * virtual functions: a function listed in primary vtables is owned by the base-most
    class whose vtable lists it (that is where it was declared/defined).

Result: roles {func_va: (class_td, role)} and symbol names. Names are real MSVC
mangling where it is certain (virtual dtor `??1`, `??_G`, `??_E`, no-arg ctor `??0`),
and readable `Ns::Class::vfN` / `ctor_argsN` otherwise.
"""

import bisect
import re
import struct
from collections import defaultdict

TEST_DELETE = b"\xF6\x44\x24\x08\x01"  # test byte ptr [esp+8], 1   (delete this?)
TEST_VECTOR = b"\xF6\x44\x24\x08\x02"  # test byte ptr [esp+8], 2   (array form)


def pretty(td):
    """'Alien@Sexy@@' -> 'Sexy::Alien'   ('?$vec@H@std@@' templates kept verbatim)."""
    parts = [p for p in td.split("@") if p]
    return "::".join(reversed(parts)) if parts else td


def td_core(td_name):
    """'.?AVAlien@Sexy@@' -> 'Alien@Sexy@@'."""
    return td_name[4:]


# ---------------------------------------------------------------------------
def parse_rtti(img, scan):
    """classes: core_name -> dict(vtables={offset: va}, parents=[core,...], bases_all=[core,...])"""
    tds = scan["tds"]
    classes = {}
    for vt, (off, tdname, _tdva, col) in scan["vtables"].items():
        core = td_core(tdname)
        c = classes.get(core)
        if c is None:
            c = classes[core] = dict(core=core, vtables={}, parents=[], bases_all=[], col=col)
            raw = img.read(col, 20)
            if len(raw) == 20:
                _sig, _o, _cd, _ptd, pchd = struct.unpack("<5I", raw)
                chd = img.read(pchd, 16)
                if len(chd) == 16:
                    _s, _a, n, pbca = struct.unpack("<4I", chd)
                    bases = []
                    for i in range(min(n, 256)):
                        pb = img.u32(pbca + 4 * i)
                        b = img.read(pb, 28) if pb else b""
                        if len(b) == 28:
                            ptd, ncont, md, _pd, _vd, _at, _pc = struct.unpack("<7I", b)
                            bases.append((td_core(tds.get(ptd, ".?AV?@@")), ncont, md))
                    c["bases_all"] = [b[0] for b in bases[1:]]
                    if bases:  # direct bases = children of entry 0 in the preorder list
                        j, end = 1, 1 + bases[0][1]
                        while j < end and j < len(bases):
                            c["parents"].append(bases[j][0])
                            j += 1 + bases[j][1]
        c["vtables"][off] = vt
    return classes


def vtable_slots(img, va, stop_at):
    out = []
    for k in range(4096):
        a = va + 4 * k
        if k and a in stop_at:
            break
        f = img.u32(a)
        if not (f and img.is_code(f)):
            break
        out.append(f)
    return out


# ---------------------------------------------------------------------------
def find_vptr_writes(img, vt_to_class):
    """-> list of (code_va, vtable_va, kind, disp) for stores/loads of a vtable address."""
    hits = []
    if not vt_to_class:
        return hits
    pat = re.compile(b"|".join(re.escape(struct.pack("<I", v)) for v in vt_to_class))
    for s in img.secs:
        if not s["chars"] & 0x20:
            continue
        tb = img.sec_bytes(s)
        for m in pat.finditer(tb):
            o = m.start()
            vt = struct.unpack("<I", m.group(0))[0]
            kind = None
            disp = 0
            for k in (2, 3, 4, 6, 7):  # C7 /0 modrm [sib] [disp] imm32
                p = o - k
                if p < 0 or tb[p] != 0xC7:
                    continue
                modrm = tb[p + 1]
                mod, reg, rm = modrm >> 6, (modrm >> 3) & 7, modrm & 7
                if reg != 0 or mod == 3:
                    continue
                ln = 2
                stacky = (rm == 5 and mod in (1, 2))  # [ebp+disp]
                if rm == 4:
                    stacky = stacky or (tb[p + 2] & 7) == 4  # SIB base = esp
                    ln += 1
                if mod == 1:
                    d, ln = tb[p + ln], ln + 1
                    disp = d - 256 if d > 127 else d
                elif mod == 2:
                    disp, ln = struct.unpack_from("<i", tb, p + ln)[0], ln + 4
                elif mod == 0 and rm == 5:
                    ln += 4
                if p + ln == o:
                    kind = "stack" if stacky else ("global" if (mod == 0 and rm == 5) else "store")
                    break
            if kind is None and o >= 1 and 0xB8 <= tb[o - 1] <= 0xBF:
                kind = "load"
            if kind and kind != "stack":
                hits.append((s["lo"] + o, vt, kind, disp))
    return hits


# ---------------------------------------------------------------------------
def analyze_classes(img, scan, func_starts):
    """func_starts: sorted list of all known function start addresses.
    -> dict(classes, roles, names, objects)"""
    classes = parse_rtti(img, scan)
    vt_set = set(scan["vtables"])
    cols_loc = {v - 4 for v in vt_set}  # where the next vtable's COL pointer sits
    vt_class, vt_off = {}, {}
    for core, c in classes.items():
        for off, vt in c["vtables"].items():
            vt_class[vt], vt_off[vt] = core, off
    for core, c in classes.items():
        c["slots"] = {off: vtable_slots(img, vt, cols_loc) for off, vt in c["vtables"].items()}

    anc = {}  # transitive ancestors, from the CHD list
    for core, c in classes.items():
        anc[core] = set(c["bases_all"])

    def func_of(addr):
        i = bisect.bisect_right(func_starts, addr) - 1
        return func_starts[i] if i >= 0 else None

    def func_bytes(f):
        i = bisect.bisect_right(func_starts, f)
        end = func_starts[i] if i < len(func_starts) else f + 0x200
        return img.read(f, min(end - f, 0x400))

    roles = {}  # func -> (core, role, extra)
    names = {}

    # ---- deleting-destructor wrappers + real dtors, from vtable[0] -----------
    # The wrapper in slot 0 is shared with derived classes that don't override the dtor,
    # so it belongs to the base-most class listing it. ??_G (scalar) and ??_E (vector)
    # deleting dtors have identical bodies in this compiler and the name can't be
    # recovered from the code (a "root gets ??_E" guess was only 56% right against
    # the PvZ map), so it is named neutrally.
    wrap_cls = defaultdict(set)
    for core, c in classes.items():
        s0 = c["slots"].get(0, [])
        if s0:
            fb = func_bytes(s0[0])
            k = fb.find(TEST_DELETE)
            if k >= 0 and fb[k + 5 : k + 6] == b"\x74":
                wrap_cls[s0[0]].add(core)
    dtor_of = {}
    for w, owners in wrap_cls.items():
        roots = [c for c in owners if not (anc[c] & owners)]
        core = sorted(roots)[0]
        roles[w] = (core, "ddtor", None)
        names[w] = f"{pretty(core)}::deleting_dtor"
        fb = func_bytes(w)
        k = fb.find(TEST_DELETE)
        tgt = None
        for m in re.finditer(rb"\xE8(....)", fb[:k], re.S):
            rel = struct.unpack("<i", m[1])[0]
            t = w + m.start() + 5 + rel
            if img.is_code(t):
                tgt = t
        if tgt and tgt not in roles:
            dtor_of[core] = tgt

    # ---- vptr writes -> ctor / dtor candidates --------------------------------
    per_func = defaultdict(list)
    for addr, vt, kind, disp in find_vptr_writes(img, vt_class):
        f = func_of(addr)
        if f is not None:
            per_func[f].append((addr, vt, kind, disp))

    for f, ws in per_func.items():
        if f in roles:
            continue
        # only writes into `this` itself (disp 0) can be the class's own ctor/dtor; a write at
        # [reg+N] initialises a base subobject inside some larger (maybe RTTI-less) class
        own = [vt_class[vt] for a, vt, kind, disp in ws if vt_off[vt] == 0 and disp == 0 and kind in ("store", "load")]
        if not own:
            continue
        uniq = list(dict.fromkeys(own))
        # most derived = the class every other written class is an ancestor of
        best = [c for c in uniq if all(o == c or o in anc[c] for o in uniq)]
        if not best:
            roles[f] = (uniq[-1], "vptr_multi", None)
            continue
        core = best[0]
        if dtor_of.get(core) == f:
            roles[f] = (core, "dtor", None)
        else:
            roles[f] = (core, "ctor", None)
    for core, d in dtor_of.items():
        if d not in roles:  # dtor with no vptr write of its own
            roles[d] = (core, "dtor", None)
        elif roles[d][1] != "dtor" and roles[d][0] == core:
            roles[d] = (core, "dtor", None)

    # ---- ctor/dtor names ----------------------------------------------------------
    def argbytes(f):
        fb = func_bytes(f).rstrip(b"\xCC")
        if fb[-1:] == b"\xC3":
            return 0
        if len(fb) >= 3 and fb[-3] == 0xC2:
            return struct.unpack("<H", fb[-2:])[0]
        return None

    ctor_seen = defaultdict(int)
    for f, (core, role, _) in sorted(roles.items()):
        if role == "dtor":
            names[f] = f"??1{core}UAE@XZ"
        elif role == "ctor":
            a = argbytes(f)
            ctor_seen[core] += 1
            if a == 0 and ctor_seen[core] == 1:
                names[f] = f"??0{core}QAE@XZ"
            else:
                names[f] = f"{pretty(core)}::ctor_{ctor_seen[core]}" + (f"_args{a}" if a else "")

    # ---- virtual function ownership (primary vtables) ---------------------------
    in_vt = defaultdict(set)  # func -> {(core, slot)}
    for core, c in classes.items():
        for k, f in enumerate(c["slots"].get(0, [])):
            in_vt[f].add((core, k))
    for f, cs in in_vt.items():
        if f in roles:
            continue
        owners = {c for c, _ in cs}
        roots = [c for c in owners if not (anc[c] & owners)]
        if len(roots) == 1:
            slot = min(k for c, k in cs if c == roots[0])
            roles[f] = (roots[0], "virtual", slot)
            names[f] = f"{pretty(roots[0])}::vf{slot}"

    # ---- secondary-vtable thunks belong to the complete class ---------------------
    for core, c in classes.items():
        for off, sl in c["slots"].items():
            if off == 0:
                continue
            for k, f in enumerate(sl):
                if f not in roles:
                    roles[f] = (core, "thunk", (off, k))
                    names[f] = f"{pretty(core)}::thunk{off}_vf{k}"

    # ---- RTTI data object names (only the ones whose naming is unambiguous) ----
    objects = {}
    for core, c in classes.items():
        objects[c["col"]] = (f"??_R4{core}6B@", 20)
        chd = img.u32(c["col"] + 16)
        if chd:
            objects[chd] = (f"??_R3{core}8", 16)
            pbca = img.u32(chd + 12)
            if pbca:
                objects[pbca] = (f"??_R2{core}8", 4 * (len(c["bases_all"]) + 1))
    return dict(classes=classes, roles=roles, names=names, objects=objects, dtor_of=dtor_of)


# ---------------------------------------------------------------------------
# TU segmentation
# ---------------------------------------------------------------------------
def outer_class(core, classes):
    """Nested classes (`Inner@Outer@Ns@@`) live in their outermost *known* class's TU."""
    parts = [p for p in core.split("@") if p]
    for k in range(len(parts) - 1, 0, -1):  # outermost (longest suffix) first
        cand = "@".join(parts[k:]) + "@@"
        if cand in classes:
            return cand
    return core


def tu_key_for_class(core):
    parts = [p for p in core.split("@") if p]
    if not parts:
        return "unmapped/unknown.cpp"
    name = re.sub(r"[^\w$.-]", "_", parts[0])[:60]
    ns = [re.sub(r"[^\w$.-]", "_", p)[:40] for p in reversed(parts[1:])]
    return "/".join(ns + [name + ".cpp"])


def call_edges(img, funcs):
    """caller -> {callee} over E8/E9 rel32 between known function starts."""
    fs = sorted(funcs)
    fset = set(fs)
    edges = defaultdict(set)
    for s in img.secs:
        if not s["chars"] & 0x20:
            continue
        tb = img.sec_bytes(s)
        for m in re.finditer(rb"[\xE8\xE9](....)", tb, re.S):
            rel = struct.unpack("<i", m[1])[0]
            site = s["lo"] + m.start()
            t = site + 5 + rel
            if t in fset:
                i = bisect.bisect_right(fs, site) - 1
                if i >= 0 and fs[i] != t:
                    edges[fs[i]].add(t)
    return edges


def segment(main_funcs, anchors, edges, lam=1.0, eps=0.02, w=0.15, mismatch=1.0):
    """Viterbi segmentation of the address-ordered function list into runs, one label each.

    main_funcs: sorted addresses; anchors: {func: label}; edges: caller -> {callee}.
    Cost: `mismatch` for every anchored function whose label differs from its segment's
    (set above `lam` so RTTI evidence outranks position -- needed when a build interleaves classes),
    `lam` per label switch, `eps` per un-anchored function inside a class segment (so long
    stretches nobody claims fall back to 'default'), minus `w` per call edge to a function
    anchored to the segment's label. Returns {func: label or None}."""
    n = len(main_funcs)
    idx = {f: i for i, f in enumerate(main_funcs)}
    labels = sorted(set(anchors.values()))
    L = len(labels) + 1  # last = default
    DEF = L - 1
    lab_i = {l: i for i, l in enumerate(labels)}
    # call votes: function index -> {label index: count}
    votes = defaultdict(lambda: defaultdict(int))
    for a, bs in edges.items():
        for b in bs:
            if a in idx and b in idx:
                if a in anchors and b not in anchors:
                    votes[idx[b]][lab_i[anchors[a]]] += 1
                if b in anchors and a not in anchors:
                    votes[idx[a]][lab_i[anchors[b]]] += 1
    INF = float("inf")
    prev = [0.0] * L
    back_stay = []  # per i: list of bool (came from same label)
    back_best = []  # per i: argmin label of previous row
    for i, f in enumerate(main_funcs):
        best = min(range(L), key=prev.__getitem__)
        bv = prev[best]
        a = anchors.get(f)
        ai = lab_i[a] if a is not None else None
        cur = [0.0] * L
        stay = [True] * L
        vt = votes.get(i)
        for l in range(L):
            keep, sw = prev[l], bv + lam
            if keep <= sw:
                base, st = keep, True
            else:
                base, st = sw, False
            if ai is not None:
                e = 0.0 if l == ai else mismatch
            elif l == DEF:
                e = 0.0
            else:
                e = eps - (w * min(vt[l], 3) if vt and l in vt else 0.0)
            cur[l] = base + e
            stay[l] = st
        back_stay.append(stay)
        back_best.append(best)
        prev = cur
    l = min(range(L), key=prev.__getitem__)
    out = [None] * n
    for i in range(n - 1, -1, -1):
        out[i] = labels[l] if l != DEF else None
        if not back_stay[i][l]:
            l = back_best[i]
    return {f: out[i] for i, f in enumerate(main_funcs)}


# ---------------------------------------------------------------------------
# glue used by analyze.py
# ---------------------------------------------------------------------------
ANCHOR_ROLES = ("ctor", "dtor", "ddtor", "virtual", "thunk")


def is_library_class(core):
    """std:: classes and template instantiations are inline library code: the compiler drops
    them into whichever TU first needed them, so they say nothing about TU boundaries."""
    return core.startswith("?$") or "@std@@" in core or core.endswith("@std@@")
SEG_PARAMS = (1.0, 0.02, 0.03, 3.0)  # lam, eps, w, mismatch -- calibrated on PvZ; mismatch>lam keeps every RTTI anchor


def class_stage(img, scan, syms, exe_stem):
    """Rename auto-named functions from RTTI roles and give every function a class TU.
    Modifies `syms` ({va: dict(name, func, tu, size)}) in place."""
    funcs = sorted(a for a, s in syms.items() if s["func"] and img.is_code(a))
    tail = {a for a in funcs if syms[a]["name"].startswith(("__unwindfunclet$", "__ehhandler$"))}
    main = [a for a in funcs if a not in tail]
    mainset = set(main)
    cr = analyze_classes(img, scan, funcs)

    used = {s["name"] for s in syms.values()}
    renamed = 0
    for va, name in sorted(cr["names"].items()):
        s = syms.get(va)
        if not s or not s["func"] or not s["name"].startswith("sub_"):
            continue
        if name in used:
            name = f"{name}_{va:08X}"
        used.add(name)
        s["name"] = name
        renamed += 1

    anchors = {
        f: outer_class(core, cr["classes"])
        for f, (core, role, _x) in cr["roles"].items()
        if role in ANCHOR_ROLES and f in mainset and not is_library_class(core)
    }
    seg = segment(main, anchors, call_edges(img, main), *SEG_PARAMS)

    key_of, run_start = {}, None
    for f in main:
        lab = seg[f]
        if lab is None:
            if run_start is None:
                run_start = f
            key_of[f] = f"unmapped/{exe_stem}_{run_start:08X}.cpp"
        else:
            run_start = None
            key_of[f] = tu_key_for_class(lab)
        syms[f]["tu"] = key_of[f]

    # EH tail (.text$x): handler stub -> the function that pushes it; funclets via FuncInfo
    stubs = {a: fi for a, fi in scan["stubs"].items() if a in syms}
    ref = {}
    if stubs:
        pat = re.compile(b"|".join(re.escape(struct.pack("<I", a)) for a in stubs))
        ms = sorted(main)
        for sec in img.secs:
            if not sec["chars"] & 0x20:
                continue
            tb = img.sec_bytes(sec)
            for m in pat.finditer(tb):
                site = sec["lo"] + m.start()
                i = bisect.bisect_right(ms, site) - 1
                if i >= 0:
                    ref.setdefault(struct.unpack("<I", m.group(0))[0], ms[i])
    tail_assigned = 0
    for st, fi in stubs.items():
        owner = ref.get(st)
        if owner is None:
            continue
        key = key_of[owner]
        for a in [st] + list(scan["fi_actions"].get(fi, [])):
            if a in syms and syms[a]["tu"] is None:
                syms[a]["tu"] = key
                tail_assigned += 1

    labels = {l for l in seg.values() if l}
    summary = (
        f"{len(cr['classes'])} RTTI classes, {len(anchors)} anchored functions, "
        f"{renamed} renamed, {len(labels)} class TUs, {tail_assigned}/{len(tail)} EH-tail functions placed"
    )
    return dict(objects=cr["objects"], summary=summary, roles=cr["roles"], seg=seg)

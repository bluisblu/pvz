#!/usr/bin/env python3
"""Binary analysis behind `python configure.py --analyze <VERSION>`.

Inputs live in orig/<VERSION>/ :
  *.exe   required  (the binary to split)
  *.map   optional  MSVC linker map   -> function/data symbol names + TU (object) ownership
  *.pdb   optional  MSVC PDB          -> exact per-module byte ranges (data splits, and
                                          TU ownership for code when there is no map)

Output: config/<VERSION>/{config.yml (created if missing), symbols.txt, splits.txt}.
Existing symbols.txt/splits.txt are backed up (*.bak, *.bak.N) first, never overwritten.

Function-boundary discovery (the part jeff does with .pdata on Xbox 360):
  * x64 PE with an exception directory: RUNTIME_FUNCTION table (begin, end, unwind),
    sorted by begin address -> exact function starts *and* sizes.
  * x86 PE32 has NO exception directory (.pdata formats exist only for MIPS, the
    Windows CE ARM/PPC/SH parts, x64 and Itanium), so the equivalent is recovered from
    MSVC C++ EH metadata instead: FuncInfo -> unwind-map actions (unwind funclets),
    try-block handlers (catch funclets) and the `mov eax, FuncInfo; jmp __CxxFrameHandler3`
    __ehhandler stubs. Plus RTTI (COL -> TypeDescriptor, vtables), import thunks, the
    entry point, vtable slots and call targets that follow function padding.
With a map those all just cross-check/supplement the map's names; without one, they
are the only source of function starts, so symbols are named sub_XXXXXXXX.
"""

import argparse
import bisect
import re
import shutil
import struct
import sys
from pathlib import Path

import pefile
sys.path.insert(0, str(Path(__file__).resolve().parent))

PUB_RE = re.compile(
    r"^\s*(?P<seg>[0-9a-fA-F]{4}):(?P<off>[0-9a-fA-F]{8})\s+(?P<name>\S+)\s+"
    r"(?P<va>[0-9a-fA-F]{8})\s+(?:(?P<f>f)\s+)?(?:i\s+)?(?P<obj>\S+)\s*$"
)
BSS_RE = re.compile(r"^\s*[0-9a-fA-F]{4}:(?P<off>[0-9a-fA-F]{8})\s+(?P<len>[0-9a-fA-F]{8})H\s+\.bss\s")
SKIP_NAME_RE = re.compile(r"^__catch\$")  # catch bodies live inside their parent function
SCN_CNT_CODE = 0x20
SCN_UNINIT = 0x80
MACHINE_X86, MACHINE_X64 = 0x14C, 0x8664


# ---------------------------------------------------------------------------
# PE image
# ---------------------------------------------------------------------------
class Image:
    def __init__(self, path):
        self.path = Path(path)
        self.pe = pefile.PE(str(path))
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.machine = self.pe.FILE_HEADER.Machine
        self.entry = self.base + self.pe.OPTIONAL_HEADER.AddressOfEntryPoint
        self.secs = []
        for s in self.pe.sections:
            lo = self.base + s.VirtualAddress
            self.secs.append(
                dict(
                    name=s.Name.rstrip(b"\0").decode(errors="replace"),
                    lo=lo,
                    hi=lo + s.Misc_VirtualSize,
                    raw=s.SizeOfRawData,
                    chars=s.Characteristics,
                )
            )

    def read(self, va, n):
        try:
            d = self.pe.get_data(va - self.base, n)
        except Exception:
            return b""
        return d

    def u32(self, va):
        b = self.read(va, 4)
        return struct.unpack("<I", b)[0] if len(b) == 4 else None

    def section_of(self, va):
        for s in self.secs:
            if s["lo"] <= va < s["hi"]:
                return s["name"]
        return None

    def is_code(self, va):
        for s in self.secs:
            if s["lo"] <= va < s["hi"]:
                return bool(s["chars"] & SCN_CNT_CODE)
        return False

    def sec_bytes(self, s):
        return self.read(s["lo"], s["hi"] - s["lo"])


# ---------------------------------------------------------------------------
# map / pdb readers
# ---------------------------------------------------------------------------
def parse_map(path):
    syms, bss = [], None
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            m = BSS_RE.match(line)
            if m:
                bss = (int(m["off"], 16), int(m["len"], 16))
            m = PUB_RE.match(line)
            if not m:
                continue
            if m["seg"] == "0000" or m["obj"] in ("<absolute>", "<linker-defined>", "<common>"):
                continue
            if SKIP_NAME_RE.match(m["name"]):
                continue
            syms.append((int(m["va"], 16), m["name"], bool(m["f"]), m["obj"]))
    return syms, bss


def _read_msf_streams(path):
    raw = Path(path).read_bytes()
    if not raw.startswith(b"Microsoft C/C++ MSF 7.00"):
        sys.exit("[-] unsupported PDB (expected MSF 7.00)")
    bs, _, _, dir_bytes, _, map_addr = struct.unpack_from("<6I", raw, 32)

    def blocks(idx):
        return b"".join(raw[i * bs : (i + 1) * bs] for i in idx)

    n_dir_blocks = -(-dir_bytes // bs)
    dir_idx = struct.unpack_from(f"<{n_dir_blocks}I", raw, map_addr * bs)
    d = blocks(dir_idx)[:dir_bytes]
    n_streams = struct.unpack_from("<I", d, 0)[0]
    sizes = struct.unpack_from(f"<{n_streams}I", d, 4)
    pos = 4 + 4 * n_streams
    streams = []
    for sz in sizes:
        if sz == 0xFFFFFFFF:
            streams.append(b"")
            continue
        nb = -(-sz // bs)
        idx = struct.unpack_from(f"<{nb}I", d, pos)
        pos += 4 * nb
        streams.append(blocks(idx)[:sz])
    return streams


def parse_pdb_contribs(path):
    """-> (modules[(modname, objname)], contribs[(pe_section_1based, offset, size, chars, module_idx)])"""
    dbi = _read_msf_streams(path)[3]
    mod_size, sc_size = struct.unpack_from("<2i", dbi, 24)
    off, modules, mod_end = 64, [], 64 + mod_size
    while off < mod_end:
        off += 64
        a = dbi.index(b"\0", off)
        b = dbi.index(b"\0", a + 1)
        modules.append((dbi[off:a].decode("latin1"), dbi[a + 1 : b].decode("latin1")))
        off = (b + 1 + 3) & ~3
    sc = dbi[mod_end : mod_end + sc_size]
    ver = struct.unpack_from("<I", sc, 0)[0]
    esz = 32 if ver == 0xF13151E4 else 28
    contribs = []
    for o in range(4, len(sc) - esz + 1, esz):
        sect, _, offset, size, chars, midx = struct.unpack_from("<HHiiIH", sc, o)
        contribs.append((sect, offset, size, chars, midx))
    return modules, contribs


# ---------------------------------------------------------------------------
# TU naming
# ---------------------------------------------------------------------------
SRC_EXTS = (".cpp", ".cc", ".cxx", ".c")


def build_src_index(src_root):
    """basename (lowercase, no ext) -> path relative to src/, for every source file.
    A basename that exists in more than one directory is ambiguous and is left out
    (those objects stay under unmapped/ until you name them in splits.txt)."""
    idx, dup = {}, set()
    root = Path(src_root)
    if root.is_dir():
        for p in sorted(root.rglob("*")):
            if p.suffix.lower() in SRC_EXTS and p.is_file():
                k = p.stem.lower()
                if k in idx:
                    dup.add(k)
                else:
                    idx[k] = p.relative_to(root).as_posix()
    for k in dup:
        del idx[k]
    return idx


def tu_key_from_map(objspec, src_idx):
    lib, _, obj = objspec.rpartition(":")
    stem = Path(obj).stem
    if not lib:
        return src_idx.get(stem.lower(), f"unmapped/{stem}.cpp")
    return f"lib/{lib}/{stem}.cpp"


def tu_key_from_pdb(modname, objname, src_idx):
    if not modname or modname.startswith(("* ", "Import:")):
        return "lib/linker/" + (re.sub(r"\W+", "_", modname).strip("_") or "misc") + ".cpp"
    stem = Path(modname.replace("\\", "/")).stem
    ostem = Path(objname.replace("\\", "/")).stem
    if objname and objname != modname and objname.lower().endswith((".lib", ".a")):
        return f"lib/{ostem}/{stem}.cpp"
    return src_idx.get(stem.lower(), f"unmapped/{stem}.cpp")


# ---------------------------------------------------------------------------
# EH / RTTI / thunk / pdata discovery
# ---------------------------------------------------------------------------
def scan_x86(img):
    """EH tables, RTTI, import thunks. Returns a dict of address sets/maps."""
    out = dict(unwind=set(), catch=set(), stubs={}, vtables={}, cols={}, tds={}, thunks={}, iat={}, fi_actions={})
    secd = {s["name"]: s for s in img.secs}
    rd = secd.get(".rdata")
    text = lambda v: v is not None and img.is_code(v)
    rdata_like = lambda v: v is not None and img.section_of(v) in (".rdata", ".data")

    # --- EH FuncInfo ---
    funcinfos = {}
    if rd:
        blob = img.sec_bytes(rd)
        for mg in (0x19930520, 0x19930521, 0x19930522):
            for m in re.finditer(re.escape(struct.pack("<I", mg)), blob):
                fi = rd["lo"] + m.start()
                if fi & 3:
                    continue
                raw = img.read(fi, 36)
                if len(raw) != 36:
                    continue
                _, maxstate, puw, ntry, ptry, nip, *_ = struct.unpack("<9I", raw)
                if maxstate > 4096 or ntry > 256 or nip > 65536:
                    continue
                if maxstate and not rdata_like(puw):
                    continue
                if ntry and not rdata_like(ptry):
                    continue
                acts, ok = [], True
                for i in range(maxstate):
                    e = img.read(puw + i * 8, 8)
                    if len(e) < 8:
                        ok = False
                        break
                    act = struct.unpack("<iI", e)[1]
                    if act and not text(act):
                        ok = False
                        break
                    acts.append(act)
                if not ok:
                    continue
                funcinfos[fi] = mg
                out["fi_actions"][fi] = [a for a in acts if a]
                out["unwind"].update(a for a in acts if a)
                for t in range(ntry):
                    tb = img.read(ptry + t * 20, 20)
                    if len(tb) < 20:
                        break
                    _, _, _, nc, pc = struct.unpack("<5I", tb)
                    for h in range(min(nc, 64)):
                        he = img.read(pc + h * 16, 16)
                        if len(he) == 16:
                            ah = struct.unpack("<4I", he)[3]
                            if text(ah):
                                out["catch"].add(ah)

    # --- __ehhandler stubs: [/GS cookie check] B8 <FuncInfo> E9 <rel32> ---
    # The /GS form is: mov edx,[esp+8]; lea eax,[edx+d]; mov ecx,[edx+d]; xor ecx,eax;
    # call __security_check_cookie (one to a few times) -- disp8 or disp32 operands.
    stub_re = re.compile(
        rb"(?:\x8B\x54\x24\x08(?:\x8D\x42.|\x8D\x82....)(?:(?:\x83\xC0.)?(?:\x8B\x4A.|\x8B\x8A....)\x33\xC8\xE8....){1,4})?"
        rb"\xB8(....)\xE9....",
        re.S,
    )
    for s in img.secs:
        if not s["chars"] & SCN_CNT_CODE:
            continue
        tb = img.sec_bytes(s)
        for m in stub_re.finditer(tb):
            fi = struct.unpack("<I", m[1])[0]
            if fi in funcinfos:
                out["stubs"][s["lo"] + m.start()] = fi

    # --- RTTI ---
    for n in (".data", ".rdata"):
        s = secd.get(n)
        if not s:
            continue
        d = img.sec_bytes(s)
        for m in re.finditer(rb"\.\?A[VU][A-Za-z0-9_@?$]+@@\x00", d):
            out["tds"][s["lo"] + m.start() - 8] = m.group(0)[:-1].decode()
    if rd and out["tds"]:
        d = img.sec_bytes(rd)
        for i in range(0, len(d) - 20, 4):
            sig, off, _cdo, ptd, pch = struct.unpack_from("<5I", d, i)
            if sig == 0 and ptd in out["tds"] and rdata_like(pch):
                out["cols"][rd["lo"] + i] = (off, out["tds"][ptd], ptd)
        for i in range(0, len(d) - 8, 4):
            p, f0 = struct.unpack_from("<II", d, i)
            if p in out["cols"] and text(f0):
                out["vtables"][rd["lo"] + i + 4] = out["cols"][p] + (p,)

    # --- imports + thunks ---
    for ent in getattr(img.pe, "DIRECTORY_ENTRY_IMPORT", []):
        for imp in ent.imports:
            if imp.name:
                out["iat"][imp.address] = imp.name.decode(errors="replace")
    for s in img.secs:
        if not s["chars"] & SCN_CNT_CODE:
            continue
        tb = img.sec_bytes(s)
        for m in re.finditer(rb"\xFF\x25(....)", tb, re.S):
            a = struct.unpack("<I", m[1])[0]
            if a in out["iat"]:
                out["thunks"][s["lo"] + m.start()] = out["iat"][a]
    return out


def scan_pdata_x64(img):
    """RUNTIME_FUNCTION {BeginRVA, EndRVA, UnwindRVA}[] from the exception directory."""
    d = img.pe.OPTIONAL_HEADER.DATA_DIRECTORY[3]
    if not d.Size or not d.VirtualAddress:
        return {}
    raw = img.read(img.base + d.VirtualAddress, d.Size)
    out = {}
    for o in range(0, len(raw) - 11, 12):
        b, e, _u = struct.unpack_from("<3I", raw, o)
        if b and e > b:
            out[img.base + b] = e - b
    return out


def call_targets(img, scan_code=True):
    """E8 rel32 targets that land in code right after function padding."""
    found = {}
    for s in img.secs:
        if not s["chars"] & SCN_CNT_CODE:
            continue
        tb = img.sec_bytes(s)
        lo, hi = s["lo"], s["hi"]
        for m in re.finditer(rb"\xE8(....)", tb, re.S):
            rel = struct.unpack("<i", m[1])[0]
            t = lo + m.start() + 5 + rel
            if not (lo < t < hi):
                continue
            k = t - lo
            prev = tb[k - 1]
            # int3/ret/ret-imm16 padding (MSVC), or zero-byte padding with 16-byte alignment (Metrowerks etc.)
            if prev == 0xCC or prev == 0xC3 or tb[k - 3] == 0xC2 or (prev == 0 and t % 16 == 0):
                found[t] = found.get(t, 0) + 1
    return found


# ---------------------------------------------------------------------------
# core
# ---------------------------------------------------------------------------
def mangled_class(td_name):
    return td_name[4:]  # ".?AVFoo@Bar@@" -> "Foo@Bar@@"


def analyze(img, map_path, pdb_path, src_idx, default_tu):
    log = {}
    # ---- sections ----------------------------------------------------------
    bss = None  # absolute va of .bss start inside .data
    map_syms = []
    if map_path:
        map_syms, bss_off = parse_map(map_path)
        data = next((s for s in img.secs if s["name"] == ".data"), None)
        if bss_off and data:
            bss = (data["lo"] + bss_off[0], bss_off[1])
    modules = contribs = None
    if pdb_path:
        modules, contribs = parse_pdb_contribs(pdb_path)
        if bss is None:
            data = next((x for x in img.secs if x["name"] == ".data"), None)
            un = [
                (img.secs[sect - 1]["lo"] + offset, img.secs[sect - 1]["lo"] + offset + size)
                for sect, offset, size, chars, _m in contribs
                if chars & SCN_UNINIT and size > 0 and 1 <= sect <= len(img.secs) and img.secs[sect - 1]["name"] == ".data"
            ]
            if data and un:
                lo = min(a for a, _ in un)
                bss = (lo, max(b for _, b in un) - lo)
    if bss is None:  # no map/pdb: .data's initialized bytes end where its raw data stops being non-zero
        data = next((s for s in img.secs if s["name"] == ".data"), None)
        if data and data["hi"] - data["lo"] > data["raw"] + 0x100:
            init = img.read(data["lo"], data["raw"]).rstrip(b"\0")
            lo = data["lo"] + ((len(init) + 3) & ~3)
            bss = (lo, data["hi"] - lo)
            log["bss"] = f"0x{lo:08X} (estimated: end of non-zero .data bytes)"
    sections = []  # (name, lo, hi, type)
    for s in img.secs:
        if s["name"] == ".reloc":
            continue
        if s["name"] == ".data" and bss:
            sections.append((".data", s["lo"], bss[0], "data"))
            sections.append((".bss", bss[0], s["hi"], "data"))
        else:
            sections.append((s["name"], s["lo"], s["hi"], "code" if s["chars"] & SCN_CNT_CODE else "data"))
    sec_of = lambda va: next((n for n, lo, hi, _ in sections if lo <= va < hi), None)
    sec_end = {n: hi for n, lo, hi, _ in sections}
    code_secs = [n for n, *_, t in sections if t == "code"]

    # ---- contribution index (TU by address) --------------------------------
    contrib_idx = []  # (lo, hi, key)
    if contribs:
        for sect, offset, size, chars, midx in contribs:
            if size > 0 and 1 <= sect <= len(img.secs) and midx < len(modules):
                lo = img.secs[sect - 1]["lo"] + offset
                contrib_idx.append((lo, lo + size, tu_key_from_pdb(*modules[midx], src_idx)))
        contrib_idx.sort()
    cstarts = [c[0] for c in contrib_idx]

    def tu_from_pdb(va):
        i = bisect.bisect_right(cstarts, va) - 1
        if i >= 0 and contrib_idx[i][0] <= va < contrib_idx[i][1]:
            return contrib_idx[i][2]
        return None

    # ---- symbols from the map ---------------------------------------------
    syms = {}  # va -> dict(name, func, tu, size)
    for va, name, is_func, obj in map_syms:
        if sec_of(va) is None:
            continue
        cur = syms.get(va)
        if cur is None or (is_func and not cur["func"]):
            syms[va] = dict(name=name, func=is_func, tu=tu_key_from_map(obj, src_idx), size=None)
    log["map_syms"] = len(syms)

    # ---- structural discovery ---------------------------------------------
    scan = scan_x86(img) if img.machine == MACHINE_X86 else None
    pdata = scan_pdata_x64(img) if img.machine == MACHINE_X64 else {}
    if img.machine not in (MACHINE_X86, MACHINE_X64):
        print(f"[-] Warning: machine 0x{img.machine:04X} is not x86/x64; only map/pdb symbols are used.")

    def add(va, name, func, tu=None, size=None, _why=None):
        if va in syms or sec_of(va) is None:
            return False
        syms[va] = dict(name=name, func=func, tu=tu, size=size)
        return True

    snap = sorted(syms)  # snapshot of map symbols; extents are judged against these
    snap_fn = {a for a, v in syms.items() if v["func"]}
    _ext = {}

    def covered(va):
        """strictly inside an existing function's trimmed extent (so not a new start)?"""
        i = bisect.bisect_left(snap, va) - 1
        if i < 0 or va in syms:
            return False
        a = snap[i]
        if a not in _ext:
            nxt = snap[i + 1] if i + 1 < len(snap) else sec_end[sec_of(a)]
            size = nxt - a
            if a in snap_fn:  # functions lose trailing int3 padding; objects keep their span
                d = img.read(a, size)
                while size > 1 and len(d) >= size and d[size - 1] == 0xCC:
                    size -= 1
            _ext[a] = a + size
        return va < _ext[a]

    added = dict(imports=0, thunks=0, vtables=0, unwind=0, stubs=0, entry=0, vslots=0, calls=0, pdata=0)
    if scan:
        for va, name in scan["iat"].items():
            added["imports"] += add(va, f"__imp_{name}", False, None, 4)
        for va, name in scan["thunks"].items():
            added["thunks"] += add(va, f"j_{name}", True, None, 6)
        for va, (off, td, tdva, _) in scan["vtables"].items():
            cls = mangled_class(td)
            added["vtables"] += add(va, f"??_7{cls}6B@" if off == 0 else f"vtbl_{va:08X}_{cls}", False)
        for va, (off, td, tdva) in scan["cols"].items():
            add(va, f"??_R4{mangled_class(td)}6B@" if off == 0 else f"col_{va:08X}", False, None, 20)
        for va, td in scan["tds"].items():
            add(va, f"??_R0{td[1:]}@8", False)
        for va in sorted(scan["stubs"]):
            if map_syms and covered(va):
                continue
            added["stubs"] += add(va, f"__ehhandler$sub_{va:08X}", True)
        for va in sorted(scan["unwind"]):
            if map_syms and covered(va):
                continue
            added["unwind"] += add(va, f"__unwindfunclet$sub_{va:08X}", True)
    for va, size in pdata.items():
        added["pdata"] += add(va, f"sub_{va:08X}", True, None, size)
    if img.is_code(img.entry):
        added["entry"] += add(img.entry, "entry", True)
    if scan:
        for va in list(scan["vtables"]):
            for k in range(4096):
                f = img.u32(va + 4 * k)
                if not (f and img.is_code(f)):
                    break
                if k and (va + 4 * k) in syms:
                    break  # ran into the next symbol (e.g. the next vtable's COL)
                if not (map_syms and covered(f)):
                    added["vslots"] += add(f, f"sub_{f:08X}", True)
        for t, n in sorted(call_targets(img).items()):
            if t in syms or (map_syms and covered(t)):
                continue
            added["calls"] += add(t, f"sub_{t:08X}", True)
    log["added"] = {k: v for k, v in added.items() if v}

    # ---- RTTI class analysis: names + class-based TUs (exe-only, x86 MSVC) ----
    if scan and scan["vtables"] and not map_syms and not contrib_idx:
        import classes as _classes

        st = _classes.class_stage(img, scan, syms, Path(img.path).stem)
        for va, (nm, sz) in st["objects"].items():
            add(va, nm, False, None, sz)
        log["classes"] = st["summary"]

    # ---- TU for symbols that have none ------------------------------------
    order = sorted(syms)
    last_tu = default_tu
    for va in order:
        s = syms[va]
        if s["tu"] is None:
            s["tu"] = tu_from_pdb(va) or (last_tu if map_syms else default_tu)
        last_tu = s["tu"]

    # ---- sizes --------------------------------------------------------------
    by_sec = {n: [] for n, *_ in sections}
    for va in order:
        by_sec[sec_of(va)].append(va)

    def trim(va, size):
        d = img.read(va, size)
        while size > 1 and len(d) >= size and d[size - 1] == 0xCC:
            size -= 1
        return size

    for n, addrs in by_sec.items():
        for i, va in enumerate(addrs):
            s = syms[va]
            end = addrs[i + 1] if i + 1 < len(addrs) else sec_end[n]
            size = s["size"] if s["size"] else end - va
            if s["func"] and n in code_secs and not s["size"]:
                size = trim(va, size)
            s["size"], s["sec"] = max(size, 1), n

    # ---- code TU runs -------------------------------------------------------
    run_list = []
    for n in code_secs:
        cur = None
        for va in by_sec[n]:
            key = syms[va]["tu"]
            if cur and cur[0] == key:
                continue
            if cur:
                cur[2] = va
            cur = [key, va, None, n]
            run_list.append(cur)
        if cur:
            cur[2] = sec_end[n]
            first = next(r for r in run_list if r[3] == n)
            first[1] = next(lo for nn, lo, hi, _ in sections if nn == n)

    # ---- data ranges --------------------------------------------------------
    data_ranges = {}  # key -> [(sec, lo, hi)]
    data_secs = [(n, lo, hi) for n, lo, hi, t in sections if t == "data"]
    if contrib_idx:
        owned = {}
        for lo, hi, key in contrib_idx:
            for n, slo, shi in data_secs:
                if n == ".rsrc":
                    continue
                a, b = max(lo, slo), min(hi, shi)
                if a < b:
                    owned.setdefault(n, []).append((a, b, key))
        for n, slo, shi in data_secs:
            if n == ".rsrc" or n not in owned:
                data_ranges.setdefault(f"__data/{n.lstrip('.')}.cpp", []).append((n, slo, shi))
                continue
            merged = []
            for a, b, k in sorted(owned[n]):
                if merged and merged[-1][2] == k and a <= merged[-1][1]:
                    merged[-1][1] = max(merged[-1][1], b)
                elif merged and a < merged[-1][1]:
                    a = merged[-1][1]
                    if a < b:
                        merged.append([a, b, k])
                else:
                    merged.append([a, b, k])
            merged[0][0] = min(merged[0][0], slo)
            merged[-1][1] = max(merged[-1][1], shi)
            for a, b, k in merged:
                data_ranges.setdefault(k, []).append((n, a, b))
    else:
        for n, slo, shi in data_secs:
            data_ranges[f"__data/{n.lstrip('.')}.cpp"] = [(n, slo, shi)]
    return dict(sections=sections, syms=syms, order=order, runs=run_list, data=data_ranges, log=log, scan=scan)


# ---------------------------------------------------------------------------
# writers
# ---------------------------------------------------------------------------
def _backup_and_write(path, text):
    """Write path, first saving any differing previous version as <name>.bak
    (or <name>.bak.N if that already exists) so no earlier file is ever lost."""
    path = Path(path)
    if path.exists() and path.read_text(encoding="utf-8") != text:
        bak = Path(str(path) + ".bak")
        n = 0
        while bak.exists():
            n += 1
            bak = Path(f"{path}.bak.{n}")
        shutil.copy2(path, bak)
        _BACKUPS.append(bak)
    path.write_text(text, encoding="utf-8")


_BACKUPS = []


def write_outputs(res, outdir, label):
    out = Path(outdir)
    out.mkdir(parents=True, exist_ok=True)
    lines = []
    for va in res["order"]:
        s = res["syms"][va]
        lines.append(
            f"{s['name']} = {s['sec']}:0x{va:08X}; // type:{'function' if s['func'] else 'object'} size:0x{s['size']:x}"
        )
    _backup_and_write(out / "symbols.txt", "\n".join(lines) + "\n")

    by_key, order = {}, []
    for key, lo, hi, n in res["runs"]:
        if key not in by_key:
            by_key[key] = []
            order.append(key)
        by_key[key].append((n, lo, hi))
    sp = [
        f"# {label} splits.txt (generated by scripts/analyze.py)",
        "# 'end' is exclusive. Hand-edit; --analyze keeps a .bak of the previous file.",
        "",
        "Sections:",
    ]
    for n, _, _, t in res["sections"]:
        sp.append(f"\t{n:<12} type:{t:<5} align:4")
    sp.append("")
    for key in order:
        sp.append(f"{key}:")
        for n, lo, hi in by_key[key]:
            sp.append(f"\t{n:<12} start:0x{lo:08X} end:0x{hi:08X}")
        sp.append("")
    for key, rs in res["data"].items():
        sp.append(f"{key}:")
        for n, a, b in sorted(rs, key=lambda r: r[1]):
            sp.append(f"\t{n:<12} start:0x{a:08X} end:0x{b:08X}")
        sp.append("")
    _backup_and_write(out / "splits.txt", "\n".join(sp))
    return len(lines), len(order)


DEFAULT_DELINK_VERSION = "v0.15.0"

GENERIC_CONFIG = """\
# @VERSION@ build config -- AUTO-CREATED by `configure.py --analyze @VERSION@`.
# Game-neutral defaults derived from @EXE@; review the compiler and link settings
# (include_dirs, base_flags, libs) for your project.

delink:
  repo: "HaydnTrigg/delink"
  version: "@DELINK@"
  asset_name: "delink-{os}-{arch}{ext}"

# symbols.txt / splits.txt are generated by --analyze and are the source of truth
# afterwards: edit them by hand and `ninja` re-splits. File keys in splits.txt are
# source paths relative to src/ and ARE the TU names.
target:
  binary: "orig/{version}/@EXE@"
  symbols: "config/{version}/symbols.txt"
  splits: "config/{version}/splits.txt"

  # Fields symbols.txt/splits.txt can't carry (forwarded to scripts/symbols_splits_to_json.py).
  ida:
    arch: "x86"
    procname: "x86"
    bits: @BITS@
    endian: "little"
    filetype: "PE"
    image_base: "@BASE@"
    input_file: "@EXE@"

compiler:
  id: msvc8
  toolchain:
    env: "MSVC8_DIR"
    repo: "widberg/msvc8.0"
    ref: "d6c4aa208c8345c78a9f68ba6ef911ee94c6a6e1"
  arch: x86

  # Extra system include dirs, e.g. a DirectX SDK:
  #   - env: "DXSDK_DIR"
  #     fallback: 'C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)'
  #     subpath: "Include"
  extra_includes: []

  include_dirs:
    - "src"

  base_flags: >-
    /nologo /EHsc /MT /O2 /Ob2 /Oi /Gy /GS-

link:
  enabled: false # compile-only until the objs match well enough to relink

  output: "@EXE@"
  subsystem: "@SUBSYSTEM@"
  target: "@TARGET@"

  base_address: "@BASE@"
  stack_reserve: "@STACKR@"
  stack_commit: "@STACKC@"

  # Import libraries inferred from the binary's import table; trim as needed.
  libs:
@LIBS@

  extra_flags: >-
    /MAP /OPT:REF /OPT:NOICF /INCREMENTAL:NO /FORCE:MULTIPLE

  # status:
  #   matching:
  #     - "path/to/File.cpp"

objdiff:
  min_version: "2.0.0-beta.5"
  unit_prefix: "main"
  progress_categories: ["game"]
  watch_patterns:
    - "*.c"
    - "*.cp"
    - "*.cpp"
    - "*.h"
    - "*.hpp"
    - "*.inc"
    - "*.py"
    - "*.yml"
    - "*.txt"
    - "*.json"
"""


def create_config(name, cfg_dir, exe_name, img, config_root, template=None):
    """Create config/<name>/config.yml.

    Default: a game-neutral template filled in from the PE itself (image base,
    bitness, subsystem, DLL/EXE, stack sizes, import libs). With `template`
    (the name of an existing version) that version's config.yml is cloned
    instead -- an explicit choice, never an implicit default."""
    cfg_dir.mkdir(parents=True, exist_ok=True)
    if template:
        src = Path(config_root) / template
        f = next((src / fn for fn in ("config.yml", "config.example.yml") if (src / fn).exists()), None)
        if not f:
            sys.exit(f"[-] --template {template}: no config.yml in config/{template}/")
        text = f.read_text(encoding="utf-8")
        old_exe = re.search(r'binary:\s*"orig/\{version\}/([^"]+)"', text)
        if old_exe:
            text = text.replace(old_exe[1], exe_name)
        text = text.replace(template, name)
        text = re.sub(r'(image_base:\s*)"0x[0-9A-Fa-f]+"', rf'\1"0x{img.base:08X}"', text)
        (cfg_dir / "config.yml").write_text(
            f"# AUTO-CREATED by `configure.py --analyze {name} --template {template}`. Review it.\n" + text,
            encoding="utf-8",
        )
        return f"config/{template}"

    oh = img.pe.OPTIONAL_HEADER
    libs = []
    for ent in getattr(img.pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll = ent.dll.decode(errors="replace").lower()
        if dll.startswith("api-ms-win-") or not dll.endswith(".dll"):
            continue
        lib = dll[:-4] + ".lib"
        if lib not in libs:
            libs.append(lib)
    fields = {
        "@VERSION@": name,
        "@EXE@": exe_name,
        "@DELINK@": DEFAULT_DELINK_VERSION,
        "@BITS@": "64" if img.machine == MACHINE_X64 else "32",
        "@BASE@": f"0x{img.base:08X}",
        "@SUBSYSTEM@": "console" if oh.Subsystem == 3 else "windows",
        "@TARGET@": "dll" if img.pe.FILE_HEADER.Characteristics & 0x2000 else "exe",
        "@STACKR@": f"0x{oh.SizeOfStackReserve:X}",
        "@STACKC@": f"0x{oh.SizeOfStackCommit:X}",
        "@LIBS@": "\n".join(f'    - "{l}"' for l in libs) or "    []",
    }
    text = GENERIC_CONFIG
    for k, v in fields.items():
        text = text.replace(k, v)
    (cfg_dir / "config.yml").write_text(text, encoding="utf-8")
    return "built-in generic template"


def analyze_version(name, config_root=Path("config"), orig_root=Path("orig"), src_root=Path("src"), template=None):
    orig = orig_root / name
    if not orig.is_dir():
        hit = next((p for p in orig_root.iterdir() if p.is_dir() and p.name.lower() == name.lower()), None) if orig_root.is_dir() else None
        if not hit:
            avail = sorted(p.name for p in orig_root.iterdir() if p.is_dir()) if orig_root.is_dir() else []
            sys.exit(f"[-] orig/{name}/ not found (have: {', '.join(avail) or 'nothing'}). Put the .exe (and optionally .map/.pdb) there.")
        orig, name = hit, hit.name
    exes = sorted(orig.glob("*.exe")) + sorted(orig.glob("*.dll"))
    if not exes:
        sys.exit(f"[-] No .exe in {orig}/")
    cfg_dir = Path(config_root) / name
    exe = exes[0]
    if len(exes) > 1:
        cfg = cfg_dir / "config.yml"
        if cfg.exists():
            m = re.search(r'binary:\s*"[^"]*/([^"/]+)"', cfg.read_text())
            exe = next((e for e in exes if m and e.name == m[1]), exe)
        print(f"[*] Multiple binaries in {orig}/; using {exe.name}.")
    maps, pdbs = sorted(orig.glob("*.map")), sorted(orig.glob("*.pdb"))
    map_path = next((m for m in maps if m.stem == exe.stem), maps[0] if maps else None)
    pdb_path = next((p for p in pdbs if p.stem == exe.stem), pdbs[0] if pdbs else None)

    print(f"[*] Analyzing {exe}  (map: {map_path.name if map_path else '-'}, pdb: {pdb_path.name if pdb_path else '-'})")
    img = Image(exe)
    if img.machine not in (MACHINE_X86, MACHINE_X64):
        print(f"[-] Warning: unsupported machine type 0x{img.machine:04X}.")

    if not (cfg_dir / "config.yml").exists():
        how = create_config(name, cfg_dir, exe.name, img, config_root, template)
        print(f"[+] Created {cfg_dir}/config.yml from {how}")
        created = True
    else:
        created = False

    res = analyze(img, map_path, pdb_path, build_src_index(src_root), default_tu=f"unmapped/{exe.stem}.cpp")
    n_sym, n_tu = write_outputs(res, cfg_dir, name)

    log = res["log"]
    print(f"[+] {cfg_dir}/symbols.txt: {n_sym} symbols  |  splits.txt: {n_tu} code TUs, {len(res['data'])} data owners")
    if log.get("added"):
        print("[*] Discovered beyond the map/pdb: " + ", ".join(f"{v} {k}" for k, v in log["added"].items()))
    if log.get("bss"):
        print(f"[*] .bss start {log['bss']}; supply a .map/.pdb to make it exact")
    if log.get("classes"):
        print(f"[*] RTTI class analysis: {log['classes']}")
    if not map_path:
        print("[*] No .map: names are RTTI-derived (ctor/dtor/vfN), imports, or sub_XXXXXXXX. "
              + ("Code TUs come from PDB modules." if pdb_path else
                 ("Code is split into class TUs from RTTI (review splits.txt)." if log.get("classes") else
                  f"Code is one TU (unmapped/{exe.stem}.cpp); split it by editing splits.txt.")))
    for b in _BACKUPS:
        print(f"[*] Previous {b.name.split('.bak')[0]} kept as {b.name}")
    print(f"[+] Next: python configure.py -v {name}" + ("   (review config/%s/config.yml first)" % name if created else ""))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("version")
    ap.add_argument("--template", help="clone config.yml from this existing version instead of the generic template")
    a = ap.parse_args()
    analyze_version(a.version, template=a.template)


if __name__ == "__main__":
    main()

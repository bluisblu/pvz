#!/usr/bin/env python3
"""One-off bootstrap: MSVC linker .map + PE -> symbols.txt / splits.txt.

PvZ had no symbols.txt/splits.txt of its own (they were implicit in the PDB),
so this seeds them from the 0.9.9 debug build's .map file. After running it
once, symbols.txt/splits.txt are the source of truth -- hand-edit them.

  - Section addresses come from the PE header (so .bss is carved off the
    tail of .data using the map's own .bss start).
  - Symbols: every public/static map symbol that lives in a real section.
    Aliases at the same address collapse to one entry (first one wins, 'f'
    flagged preferred). SEH funclets (__catch$ etc.) are skipped.
  - Sizes: distance to the next symbol in the same section (map has none),
    with trailing 0xCC (int3) alignment padding trimmed off functions using
    the real .text bytes from the exe.
  - TUs: the map's Lib:Object. Objects whose basename matches a file under
    src/Popcap/ get that source path (Popcap/Lawn/Almanac.cpp); everything
    else is parked under lib/<libname>/ or unmapped/ so it never collides
    with a real source file.
  - Only .text gets per-file ranges (that is all `idapro.json` uses);
    data sections get one pseudo-file each so segment extents cover the
    whole section, not just where named symbols happen to sit.
"""

import argparse
import re
import sys
from pathlib import Path

import pefile

PUB_RE = re.compile(
    r"^\s*(?P<seg>[0-9a-fA-F]{4}):(?P<off>[0-9a-fA-F]{8})\s+(?P<name>\S+)\s+"
    r"(?P<va>[0-9a-fA-F]{8})\s+(?:(?P<f>f)\s+)?(?:i\s+)?(?P<obj>\S+)\s*$"
)
SKIP_NAME_RE = re.compile(r"^__(catch|unwindfunclet|ehhandler)\$")
BSS_RE = re.compile(r"^\s*[0-9a-fA-F]{4}:(?P<off>[0-9a-fA-F]{8})\s+(?P<len>[0-9a-fA-F]{8})H\s+\.bss\s")


def load_sections(exe: Path):
    pe = pefile.PE(str(exe))
    base = pe.OPTIONAL_HEADER.ImageBase
    out = []
    for s in pe.sections:
        name = s.Name.rstrip(b"\0").decode()
        out.append((name, base + s.VirtualAddress, base + s.VirtualAddress + s.Misc_VirtualSize))
    return base, out


def parse_map(path: Path):
    syms = []  # (va, name, is_func, objkey)
    bss_off = bss_len = None
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            m = BSS_RE.match(line)
            if m:
                bss_off, bss_len = int(m["off"], 16), int(m["len"], 16)
            m = PUB_RE.match(line)
            if not m:
                continue
            if m["seg"] == "0000" or m["obj"] in ("<absolute>", "<linker-defined>", "<common>"):
                continue
            if SKIP_NAME_RE.match(m["name"]):
                continue
            syms.append((int(m["va"], 16), m["name"], bool(m["f"]), m["obj"]))
    return syms, bss_off, bss_len


def build_src_index(src_root: Path):
    idx = {}
    popcap = src_root / "Popcap"
    for p in popcap.rglob("*.cpp"):
        idx.setdefault(p.stem.lower(), p.relative_to(src_root).as_posix())
    return idx


def tu_key(objspec: str, src_idx):
    lib, _, obj = objspec.rpartition(":")
    stem = Path(obj).stem
    if not lib:
        if stem.lower() in src_idx:
            return src_idx[stem.lower()]
        return f"unmapped/{stem}.cpp"
    return f"lib/{lib}/{stem}.cpp"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("map")
    ap.add_argument("exe")
    ap.add_argument("outdir", help="config/<version> directory")
    ap.add_argument("--src", default="src")
    args = ap.parse_args()

    base, pesecs = load_sections(Path(args.exe))
    syms, bss_off, bss_len = parse_map(Path(args.map))
    src_idx = build_src_index(Path(args.src))

    data_va = next(v for n, v, _ in pesecs if n == ".data")
    sections = []  # (name, start, end, type)
    for n, lo, hi in pesecs:
        if n == ".data" and bss_off is not None:
            bss_lo = data_va + bss_off
            sections.append((".data", lo, bss_lo, "data"))
            sections.append((".bss", bss_lo, bss_lo + bss_len, "data"))
        else:
            sections.append((n, lo, hi, "code" if n == ".text" else "data"))

    def section_of(va):
        for n, lo, hi, _ in sections:
            if lo <= va < hi:
                return n
        return None

    # canonical symbol per address (prefer a function-flagged alias)
    canon = {}
    for va, name, is_func, obj in syms:
        if section_of(va) is None:
            continue
        cur = canon.get(va)
        if cur is None or (is_func and not cur[1]):
            canon[va] = (name, is_func, obj)

    by_sec = {n: [] for n, *_ in sections}
    for va in sorted(canon):
        by_sec[section_of(va)].append(va)

    sec_end = {n: hi for n, _, hi, _ in sections}
    pe = pefile.PE(args.exe)

    def trim_padding(va, size):
        data = pe.get_data(va - base, size)
        while size > 1 and data[size - 1] == 0xCC:
            size -= 1
        return size

    lines = []
    for n, *_ in sections:
        addrs = by_sec[n]
        for i, va in enumerate(addrs):
            name, is_func, _obj = canon[va]
            end = addrs[i + 1] if i + 1 < len(addrs) else sec_end[n]
            size = end - va
            if is_func and n == ".text":
                size = trim_padding(va, size)
            lines.append(
                f"{name} = {n}:0x{va:08X}; // type:{'function' if is_func else 'object'} size:0x{size:x}"
            )
    out = Path(args.outdir)
    out.mkdir(parents=True, exist_ok=True)
    (out / "symbols.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")

    # --- splits.txt (.text ranges, grouped by TU in address order) -------
    runs = []  # [key, start, end]
    for va in by_sec[".text"]:
        key = tu_key(canon[va][2], src_idx)
        if runs and runs[-1][0] == key:
            continue
        if runs:
            runs[-1][2] = va
        runs.append([key, va, None])
    if runs:
        runs[-1][2] = sec_end[".text"]

    order, by_key = [], {}
    for key, lo, hi in runs:
        if key not in by_key:
            by_key[key] = []
            order.append(key)
        by_key[key].append((lo, hi))

    sp = [
        f"# PvZ 0.9.9 splits.txt (seeded from PlantsVsZombies.map by scripts/map_to_symbols_splits.py)",
        "# 'end' is exclusive. Hand-edit from here on.",
        "",
        "Sections:",
    ]
    for n, _, _, t in sections:
        sp.append(f"\t{n:<12} type:{t:<5} align:4")
    sp.append("")
    for key in order:
        sp.append(f"{key}:")
        for lo, hi in by_key[key]:
            sp.append(f"\t.text        start:0x{lo:08X} end:0x{hi:08X}")
        sp.append("")
    for n, lo, hi, t in sections:
        if t == "data":
            sp.append(f"__data/{n.lstrip('.')}.cpp:")
            sp.append(f"\t{n:<12} start:0x{lo:08X} end:0x{hi:08X}")
            sp.append("")
    (out / "splits.txt").write_text("\n".join(sp), encoding="utf-8")

    mapped = sum(1 for k in order if not k.startswith(("lib/", "unmapped/")))
    print(
        f"wrote {len(lines)} symbols, {len(order)} TUs "
        f"({mapped} mapped to src/, {len(order) - mapped} lib/unmapped) -> {out}",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()

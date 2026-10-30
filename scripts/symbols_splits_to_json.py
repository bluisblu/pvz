#!/usr/bin/env python3
"""Converts symbols.txt and splits.txt into a delink-compatible JSON schema."""

import argparse
import bisect
import json
import re
import sys
from dataclasses import dataclass
from typing import Optional

SYMBOL_RE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>\S+):0x(?P<addr>[0-9A-Fa-f]+);"
    r"\s*//\s*type:(?P<type>\w+)\s*size:0x(?P<size>[0-9A-Fa-f]+)\s*$"
)


@dataclass
class Sym:
    name: str
    section: str
    addr: int
    type: str
    size: int


def parse_symbols(path: str) -> list[Sym]:
    syms = []
    with open(path, encoding="utf-8", errors="replace") as f:
        for lineno, raw in enumerate(f, 1):
            line = raw.rstrip("\r\n")
            if not line.strip():
                continue
            m = SYMBOL_RE.match(line)
            if not m:
                print(
                    f"warning: symbols.txt:{lineno}: unrecognized line, skipping: {line!r}",
                    file=sys.stderr,
                )
                continue
            syms.append(
                Sym(
                    name=m.group("name"),
                    section=m.group("section"),
                    addr=int(m.group("addr"), 16),
                    type=m.group("type"),
                    size=int(m.group("size"), 16),
                )
            )
    return syms


@dataclass
class SectionDef:
    name: str
    type: str
    align: int


@dataclass
class FileRange:
    file: str
    section: str
    start: int
    end: int


SECTION_DEF_RE = re.compile(
    r"^\s*(?P<name>\S+)\s+type:(?P<type>\w+)\s+align:(?P<align>\d+)\s*$"
)
FILE_HEADER_RE = re.compile(r"^(?P<file>\S+):\s*$")
RANGE_RE = re.compile(
    r"^\s*(?P<section>\S+)\s+start:0x(?P<start>[0-9A-Fa-f]+)\s+end:0x(?P<end>[0-9A-Fa-f]+)\s*$"
)


def parse_splits(path: str) -> tuple[list[SectionDef], list[FileRange]]:
    section_defs: list[SectionDef] = []
    ranges: list[FileRange] = []

    with open(path, encoding="utf-8", errors="replace") as f:
        lines = [ln.rstrip("\r\n") for ln in f]

    i = 0
    n = len(lines)

    while i < n and lines[i].strip() != "Sections:":
        i += 1
    if i == n:
        raise ValueError('splits.txt: could not find a "Sections:" block')
    i += 1

    while i < n and lines[i].strip():
        m = SECTION_DEF_RE.match(lines[i])
        if m:
            section_defs.append(
                SectionDef(
                    name=m.group("name"),
                    type=m.group("type"),
                    align=int(m.group("align")),
                )
            )
        i += 1

    current_file: Optional[str] = None
    while i < n:
        line = lines[i]
        stripped = line.strip()
        if not stripped or stripped.startswith("#"):
            i += 1
            continue
        m = FILE_HEADER_RE.match(line)
        if m and not line.startswith("\t") and not line.startswith(" "):
            current_file = m.group("file")
            i += 1
            continue
        m = RANGE_RE.match(line)
        if m and current_file is not None:
            ranges.append(
                FileRange(
                    file=current_file,
                    section=m.group("section"),
                    start=int(m.group("start"), 16),
                    end=int(m.group("end"), 16),
                )
            )
            i += 1
            continue
        i += 1

    return section_defs, ranges


class RangeIndex:
    """Provides fast address-to-file lookups per section."""

    def __init__(self, ranges: list[FileRange]):
        self._by_section: dict[str, tuple[list[int], list[FileRange]]] = {}
        by_section: dict[str, list[FileRange]] = {}
        for r in ranges:
            by_section.setdefault(r.section, []).append(r)
        for section, rs in by_section.items():
            rs.sort(key=lambda r: r.start)
            starts = [r.start for r in rs]
            self._by_section[section] = (starts, rs)

    def file_for(self, section: str, addr: int) -> Optional[str]:
        entry = self._by_section.get(section)
        if entry is None:
            return None
        starts, rs = entry
        idx = bisect.bisect_right(starts, addr) - 1
        if idx < 0:
            return None
        r = rs[idx]
        if r.start <= addr < r.end:
            return r.file
        return None


def build_segments(
    section_defs: list[SectionDef],
    ranges: list[FileRange],
    syms: list[Sym],
    bits: int,
) -> list[dict]:
    extents: dict[str, tuple[int, int]] = {}
    for r in ranges:
        lo, hi = extents.get(r.section, (r.start, r.end))
        extents[r.section] = (min(lo, r.start), max(hi, r.end))

    sym_extents: dict[str, tuple[int, int]] = {}
    for s in syms:
        lo, hi = sym_extents.get(s.section, (s.addr, s.addr + s.size))
        sym_extents[s.section] = (min(lo, s.addr), max(hi, s.addr + s.size))

    segments = []
    for sd in section_defs:
        if sd.name in extents:
            start, end = extents[sd.name]
        elif sd.name in sym_extents:
            start, end = sym_extents[sd.name]
        else:
            continue

        is_code = sd.type == "code"
        is_bss = (not is_code) and (
            sd.name.lower() == ".bss" or sd.name.lower().endswith("bss")
        )
        cls = "CODE" if is_code else ("BSS" if is_bss else "DATA")

        segments.append(
            {
                "name": sd.name,
                "start": start,
                "end": end,
                "perm_r": True,
                "perm_w": not is_code,
                "perm_x": is_code,
                "class": cls,
                "bitness": bits,
            }
        )

    # Work around a real bug in HaydnTrigg/delink's `ida-split` shared-data
    # emitter (confirmed empirically against delink 0.15.0): when more than
    # one class:"DATA" segment is present, only the FIRST one in this list
    # gets its object symbols emitted as real defined COFF symbols (correct
    # section index + offset) in __shared_data.obj. Every subsequent
    # class:"DATA" segment still gets its raw bytes embedded, but its
    # symbols are silently downgraded to unresolved externs (COFF section 0,
    # offset 0) -- which then fail at link time as "Undefined symbol" for
    # perfectly real, listed-in-symbols.txt globals, even though the bytes
    # for them are sitting right there in the object. CODE and BSS segments
    # aren't affected (BSS goes through a separate code path; there's only
    # ever one CODE segment here). The safe, project-agnostic workaround is
    # to never hand delink more than one class:"DATA" segment in the first
    # place: merge every non-code, non-BSS segment into a single contiguous
    # DATA segment spanning their combined extent.
    code_segs = [s for s in segments if s["class"] == "CODE"]
    bss_segs = [s for s in segments if s["class"] == "BSS"]
    data_segs = [s for s in segments if s["class"] == "DATA"]
    if len(data_segs) > 1:
        # Guard against merging across a CODE segment's address range: e.g.
        # a PE's "Headers" pseudo-segment sits BEFORE .text, while the real
        # data segments (.data/.rsrc/.idata/etc.) sit AFTER it -- a blind
        # min/max merge would produce a bogus segment that fully overlaps
        # .text. So: merge only the largest cluster of DATA segments that
        # don't straddle any CODE segment's [start, end) range. Any DATA
        # segment that can't join that cluster (e.g. a lone pre-.text
        # "Headers" segment) is dropped from the segment list entirely
        # rather than kept as a second standalone DATA segment -- per the
        # bug above, a second DATA segment poisons ALL of its own symbols
        # (not just the dropped one's), so keeping a tiny, rarely-referenced
        # segment (raw PE header bytes -- not real source-level globals) at
        # the cost of breaking every genuine .data/.rsrc/.idata/etc. symbol
        # is a bad trade. Its `names` entries simply end up unaddressed by
        # any segment, which is fine for PE header field labels that no
        # real TU source should ever reference by symbol name anyway.
        code_ranges = [(s["start"], s["end"]) for s in code_segs]

        def straddles_code(lo: int, hi: int) -> bool:
            return any(lo < c_end and c_start < hi for c_start, c_end in code_ranges)

        full_lo = min(s["start"] for s in data_segs)
        full_hi = max(s["end"] for s in data_segs)
        if not straddles_code(full_lo, full_hi):
            mergeable = data_segs
        else:
            last_code_end = max((c_end for _, c_end in code_ranges), default=0)
            after = [s for s in data_segs if s["start"] >= last_code_end]
            mergeable = after if len(after) >= 1 else data_segs

        if len(mergeable) >= 1:
            merged_start = min(s["start"] for s in mergeable)
            merged_end = max(s["end"] for s in mergeable)
            if len(mergeable) > 1:
                # A single [start, end) DATA segment can't carve out a
                # "hole" for a BSS range that happens to sit inside its
                # combined span (common: .data/.rsrc/.idata/.CRT sit right
                # before .bss, and .reloc sits right after it) -- if left
                # alone, delink's address-based symbol scan would find the
                # same .bss-range symbols twice (once via this merged DATA
                # segment, once via the dedicated BSS segment below) and
                # emit each of them twice into __shared_data.obj, which
                # mwld then rejects as "Multiply defined symbol". So: if any
                # BSS segment's range falls inside the merge span, split the
                # merge at that BSS range instead of spanning across it,
                # and keep only the larger resulting piece (again to avoid
                # reintroducing a second DATA segment, per the bug above).
                for bss in bss_segs:
                    if merged_start < bss["end"] and bss["start"] < merged_end:
                        before_len = max(0, bss["start"] - merged_start)
                        after_len = max(0, merged_end - bss["end"])
                        if before_len >= after_len:
                            merged_end = min(merged_end, bss["start"])
                        else:
                            merged_start = max(merged_start, bss["end"])
                merged = {
                    "name": "__merged_data",
                    "start": merged_start,
                    "end": merged_end,
                    "perm_r": True,
                    "perm_w": True,
                    "perm_x": False,
                    "class": "DATA",
                    "bitness": bits,
                }
                segments = code_segs + [merged] + bss_segs
            else:
                # Nothing to merge with -- keep the single survivor as-is
                # and drop the rest (see comment above).
                segments = code_segs + mergeable + bss_segs
    return segments


def build_functions(syms: list[Sym], idx: RangeIndex) -> list[dict]:
    return [
        {
            "start": s.addr,
            "end": s.addr + s.size,
            "name": s.name,
            "thunk": False,
            "lib": False,
            "static": False,
            "public": True,
            "thunk_target": None,
            "file": idx.file_for(s.section, s.addr),
        }
        for s in syms
        if s.type == "function"
    ]


def build_names(syms: list[Sym], idx: RangeIndex) -> list[dict]:
    return [
        {
            "addr": s.addr,
            "name": s.name,
            "public": True,
            "weak": False,
            "is_func": s.type == "function",
            "file": idx.file_for(s.section, s.addr),
        }
        for s in syms
    ]


def build_idapro(syms: list[Sym], idx: RangeIndex) -> dict:
    groups: dict[str, dict[str, dict]] = {}
    funcs = [s for s in syms if s.type == "function"]
    funcs.sort(key=lambda s: (s.section, s.addr))
    for s in funcs:
        file = idx.file_for(s.section, s.addr)
        if file is None:
            continue
        groups.setdefault(file, {})[s.name] = {
            "address": s.addr,
            "size": s.size,
            "scope": "global",
        }
    return groups


def build_meta(syms: list[Sym], args: argparse.Namespace) -> dict:
    addrs = [s.addr for s in syms]
    ends = [s.addr + s.size for s in syms]
    return {
        "arch": args.arch,
        "procname": args.procname or args.arch,
        "bits": args.bits,
        "endian": args.endian,
        "image_base": args.image_base,
        "min_ea": min(addrs) if addrs else 0,
        "max_ea": max(ends) if ends else 0,
        "filetype": args.filetype,
        "input_file": args.input_file,
    }


def parse_int_auto(s: str) -> int:
    return int(s, 16) if s.lower().startswith("0x") else int(s)


def main():
    ap = argparse.ArgumentParser(
        description="Convert symbols.txt and splits.txt to delink JSON schema."
    )
    ap.add_argument("symbols", help="path to symbols.txt")
    ap.add_argument("splits", help="path to splits.txt")
    ap.add_argument("output", help="path to output JSON")

    ap.add_argument("--arch", default="ppc", help="architecture (default: ppc)")
    ap.add_argument(
        "--procname", default=None, help="processor name (default: same as --arch)"
    )
    ap.add_argument(
        "--bits", type=int, default=32, help="address width in bits (default: 32)"
    )
    ap.add_argument(
        "--endian",
        choices=["big", "little"],
        default="big",
        help="byte order (default: big)",
    )
    ap.add_argument(
        "--filetype", default="unknown", help="executable file type (default: unknown)"
    )
    ap.add_argument(
        "--image-base",
        type=parse_int_auto,
        default=0,
        help="image base address (default: 0)",
    )
    ap.add_argument(
        "--input-file", default=None, help="original binary path/name for metadata"
    )
    ap.add_argument(
        "--indent", type=int, default=None, help="JSON output indentation level"
    )
    ap.add_argument(
        "--idapro-out",
        default=None,
        help="optional path to write idapro.json grouping file",
    )

    args = ap.parse_args()

    syms = parse_symbols(args.symbols)
    section_defs, ranges = parse_splits(args.splits)
    idx = RangeIndex(ranges)

    if args.idapro_out:
        idapro = build_idapro(syms, idx)
        with open(args.idapro_out, "w", encoding="utf-8") as f:
            json.dump(idapro, f, indent=2)
        print(f"wrote {args.idapro_out}: {len(idapro)} groups", file=sys.stderr)

    obj = {
        "delink_ida_version": 1,
        "meta": build_meta(syms, args),
        "segments": build_segments(section_defs, ranges, syms, args.bits),
        "functions": build_functions(syms, idx),
        "names": build_names(syms, idx),
        "relocations": [],
    }

    with open(args.output, "w", encoding="utf-8") as f:
        json.dump(obj, f, indent=args.indent)
        if args.indent is not None:
            f.write("\n")

    print(
        f"wrote {args.output}: "
        f"{len(obj['segments'])} segments, "
        f"{len(obj['functions'])} functions, "
        f"{len(obj['names'])} names, "
        f"{len(obj['relocations'])} relocations",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()

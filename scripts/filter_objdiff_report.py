#!/usr/bin/env python3
"""
objdiff-cli's `report generate` hard-fails the *entire* report the moment
any single unit's base (freshly-compiled) object is missing from disk --
there's no "skip missing / best effort" flag as of objdiff-cli v3.7.3.

In CI, `ninja -k 0` intentionally keeps building past failures (e.g. TUs
that need the DirectX SDK, which this project's build container may not
have baked in -- see docker/Dockerfile), so some `build/<version>/src/**.obj`
paths objdiff.json lists as `base_path` may legitimately not exist yet.

Rather than have that abort progress reporting for every OTHER unit that
compiled fine, this rewrites a copy of objdiff.json to drop any unit whose
base_path is missing, immediately before running `objdiff-cli report
generate`. Units dropped this way just don't contribute a "current" data
point to that run's report -- decomp.dev / objdiff's own report-diffing
already treats a unit missing from a report as unchanged from its last
known state, so this doesn't misreport progress as having gone backwards,
it just doesn't advance for that unit until it builds again.

Usage:
    python3 filter_objdiff_report.py objdiff.json filtered_objdiff.json
"""
import json
import sys
from pathlib import Path


def main():
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <in objdiff.json> <out objdiff.json>")

    in_path, out_path = Path(sys.argv[1]), Path(sys.argv[2])
    data = json.loads(in_path.read_text())

    units = data.get("units", [])
    kept, dropped = [], []
    for unit in units:
        base_path = unit.get("base_path")
        if base_path and not Path(base_path).is_file():
            dropped.append(unit["name"])
            continue
        kept.append(unit)

    data["units"] = kept
    out_path.write_text(json.dumps(data))

    print(f"[*] {len(kept)} unit(s) kept, {len(dropped)} unit(s) dropped "
          f"(base object not yet built):")
    for name in dropped:
        print(f"    - {name}")


if __name__ == "__main__":
    main()

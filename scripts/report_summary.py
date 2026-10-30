#!/usr/bin/env python3
"""Print the headline numbers from an objdiff-cli report.json."""
import json, sys

m = json.load(open(sys.argv[1], encoding="utf-8"))["measures"]
print(f"matched functions : {m.get('matched_functions', 0)} / {m.get('total_functions', 0)}")
print(f"matched code      : {m.get('matched_code_percent', 0):.2f}%")
print(f"complete units    : {m.get('complete_units', 0)} / {m.get('total_units', 0)}")

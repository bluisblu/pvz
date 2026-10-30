#!/usr/bin/env python3
"""ninja helper: run a command quietly, print its output only on failure,
then touch a stamp file. Keeps shell syntax (>, &&) out of build.ninja so it
works the same under cmd.exe, Wine/Winlator and POSIX shells.

usage: run_split.py <stamp> <command...>
"""
import pathlib
import subprocess
import sys

stamp, cmd = sys.argv[1], sys.argv[2:]
r = subprocess.run(cmd, capture_output=True, text=True)
if r.returncode != 0:
    sys.stdout.write(r.stdout)
    sys.stderr.write(r.stderr)
    sys.exit(r.returncode)
pathlib.Path(stamp).touch()

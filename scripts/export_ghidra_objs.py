#!/usr/bin/env nix-shell
#!nix-shell -p python311 -i python3

import argparse
import os
from pathlib import Path
import tempfile
import urllib.request

import ghidra_helpers

SCRIPT_PATH = Path(os.path.realpath(__file__)).parent


def main():
    parser = argparse.ArgumentParser(
        description="Export a ghidra database history to git",
    )
    parser.add_argument("--local-project-dir", help="Path to the local ghidra project")
    parser.add_argument("--local-project-name", help="Path to the local ghidra project")
    parser.add_argument("--import-xml", action="store_true", help="Use the XML export")
    parser.add_argument(
        "--import-csv", action="store_true", help="Use the mapping.csv file"
    )
    parser.add_argument("--program", help="Program to export", default="th06_102h.exe")
    args = parser.parse_args()

    os.makedirs(str(SCRIPT_PATH.parent / "build" / "objdiff" / "orig"), exist_ok=True)

    if args.import_xml:
        with tempfile.TemporaryDirectory() as tempdir:
            filename, _ = urllib.request.urlretrieve(
                "https://raw.githubusercontent.com/happyhavoc/th06-re/xml/th06_102h.exe.xml"
            )
            ghidra_helpers.runAnalyze(
                str(tempdir),
                "Touhou 06",
                import_file=str(SCRIPT_PATH.parent / "resources" / "game.exe"),
                analysis=True,
                post_scripts=[
                    ["ImportFromXml.java", filename],
                    [
                        "ExportDelinker.java",
                        str(SCRIPT_PATH.parent / "config" / "ghidra_ns_to_obj.csv"),
                        str(SCRIPT_PATH.parent / "build" / "objdiff" / "orig"),
                    ],
                ],
            )
    elif args.import_csv:
        with tempfile.TemporaryDirectory() as tempdir:
            mapping_csv = SCRIPT_PATH.parent / "config" / "mapping.csv"
            ghidra_helpers.runAnalyze(
                str(tempdir),
                "Touhou 06",
                import_file=str(SCRIPT_PATH.parent / "resources" / "game.exe"),
                analysis=True,
                post_scripts=[
                    ["ImportFromCsv.java", str(mapping_csv)],
                    [
                        "ExportDelinker.java",
                        str(SCRIPT_PATH.parent / "config" / "ghidra_ns_to_obj.csv"),
                        str(SCRIPT_PATH.parent / "build" / "objdiff" / "orig"),
                    ],
                ],
            )
    else:
        repo = args.local_project_dir
        project_name = args.local_project_name
        program = args.program

        ghidra_helpers.runAnalyze(
            repo,
            project_name,
            process=program,
            pre_scripts=[
                [
                    "ExportDelinker.java",
                    str(SCRIPT_PATH.parent / "config" / "ghidra_ns_to_obj.csv"),
                    str(SCRIPT_PATH.parent / "build" / "objdiff" / "orig"),
                ]
            ],
        )


if __name__ == "__main__":
    main()

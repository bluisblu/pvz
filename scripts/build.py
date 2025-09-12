import argparse
from pathlib import Path
from winhelpers import run_windows_program
import sys
import subprocess
import os

# Map relative source paths to additional compiler flags
# e.g. "src/Plant.cpp" needs /Ob0 to prevent inlining
PER_FILE_FLAGS = {
    "src/Plant.cpp": "-Ob0",
    "src/SexyAppFramework/BassLoader.cpp": "/Ob0",
    "src/SexyAppFramework/Font.cpp": "/Ob0",
    "src/SexyAppFramework/HTTPTransfer.cpp": "/Ob0",
    "src/SexyAppFramework/NativeDisplay.cpp": "/Ob0",
    #"src/SexyAppFramework/SexyTransform2D.cpp": "/Ob0", # ???
}


def build_object(source_file: Path, out_dir: Path, verbose: bool = False) -> Path:
    try:
        rel_path = source_file.relative_to("src")
    except ValueError:
        rel_path = Path(source_file.name)

    obj_file = out_dir / rel_path.with_suffix(".obj")
    obj_file.parent.mkdir(parents=True, exist_ok=True)

    # Detect DirectX SDK path
    dxsdk_dir = os.environ.get("DXSDK_DIR") or r"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)"
    dx_include = Path(dxsdk_dir) / "Include"
    if not dx_include.exists():
        raise RuntimeError(f"DirectX SDK include folder not found at {dx_include}")

    vcvarsall = r"C:\Program Files (x86)\Microsoft Visual Studio 8\VC\vcvarsall.bat"
    if not Path(vcvarsall).exists():
        raise RuntimeError(f"Cannot find vcvarsall.bat at {vcvarsall}")

    # Base compiler flags
    base_flags = (
        '/nologo /EHsc /MD /O2 /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATE '
        f'/I"{dx_include}" /I"{Path("src/SexyAppFramework").resolve()}" /I"{Path("src").resolve()}"'
    )

    # Check per-file flags
    rel_source_str = str(source_file).replace("\\", "/")
    per_file_flags = PER_FILE_FLAGS.get(rel_source_str, "")

    # Build compile command
    cmd = (
        f'"{vcvarsall}" x86 && '
        f'cl.exe /c "{source_file.resolve()}" '
        f'/Fo"{obj_file.resolve()}" '
        f'{base_flags} {per_file_flags}'
    )

    if verbose:
        print(f"Running: {cmd}")

    subprocess.check_call(cmd, shell=True)

    return obj_file


def find_source_for_obj(obj_name: Path) -> Path:
    """
    Given an object file path, try to locate the matching .c/.cpp source in ./src.
    """
    base_name = obj_name.stem  # e.g. "Plant" from "Plant.obj"
    src_dir = Path("src")
    candidates = list(src_dir.rglob(base_name + ".c")) + list(src_dir.rglob(base_name + ".cpp"))

    if not candidates:
        print(f"Error: Could not find source file for {obj_name} in {src_dir}", file=sys.stderr)
        sys.exit(1)
    if len(candidates) > 1:
        print(f"Warning: Multiple candidates found for {obj_name}, using {candidates[0]}")
    return candidates[0]


def parse_args():
    parser = argparse.ArgumentParser(description="Build .obj files for PvZ")
    parser.add_argument(
        "--source",
        nargs="+",
        help="Source file(s) to compile into .obj"
    )
    parser.add_argument(
        "--out-dir",
        default=None,
        help="Directory where object files will be placed"
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Show MSVC compiler output"
    )
    parser.add_argument(
        "--build-type",
        choices=["normal", "objdiffbuild"],
        default="normal",
        help="Type of build: normal or objdiffbuild"
    )
    parser.add_argument(
        "--object-name",
        help="Specific object file to build in objdiffbuild mode"
    )
    return parser.parse_args()


def main():
    args = parse_args()

    if args.build_type == "objdiffbuild":
        if not args.object_name:
            print("Error: --object-name must be specified for objdiffbuild", file=sys.stderr)
            sys.exit(1)

        obj_path = Path(args.object_name)
        src_path = find_source_for_obj(obj_path)

        # Default out-dir for objdiffbuild
        out_dir = Path(args.out_dir) if args.out_dir else Path("build/objdiff/reimpl")
        out_dir.mkdir(parents=True, exist_ok=True)

        obj_file = build_object(src_path, out_dir, verbose=args.verbose)
        print(f"Objdiff build: {src_path} -> {obj_file}")

    else:
        out_dir = Path(args.out_dir or "build/obj")
        out_dir.mkdir(parents=True, exist_ok=True)

        if not args.source:
            print("Error: --source must be specified for normal builds", file=sys.stderr)
            sys.exit(1)

        for src in args.source:
            src_path = Path(src)
            obj_file = build_object(src_path, out_dir, verbose=args.verbose)
            print(f"Compiled: {src_path} -> {obj_file}")


if __name__ == "__main__":
    main()

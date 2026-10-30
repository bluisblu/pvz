#!/usr/bin/env python3
"""
Generic configure script for a decomp-toolkit-style workflow:
symbols.txt + splits.txt -> delink ida-split -> ninja build -> objdiff.json.

This script is intentionally free of game/compiler-specific hardcoding.
All of that lives in config/<version>/config.yml, copied from
config.example.yml. To fork this project for a different game or
compiler, edit that YAML file — you should not need to touch this
file at all.
"""

import argparse
import json
import os
import platform
import shutil
import stat
import subprocess
import sys
import urllib.request
import zipfile
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

try:
    import yaml
except ImportError:
    sys.exit("[-] Missing dependency 'pyyaml'. Install it with: pip install pyyaml")



# ---------------------------------------------------------------------------
# Config loading
# ---------------------------------------------------------------------------


def discover_versions(config_root: Path) -> list:
    if not config_root.exists():
        return []
    return sorted(
        p.name
        for p in config_root.iterdir()
        if (p / "config.yml").exists() or (p / "config.example.yml").exists()
    )


def load_config(config_root: Path, version: str) -> Dict[str, Any]:
    version_dir = config_root / version
    config_file = version_dir / "config.yml"

    if not config_file.exists():
        sys.exit(f"[-] No config found for version '{version}' at {config_file}")
    with open(config_file, "r") as f:
        return yaml.safe_load(f) or {}


def resolve_env_path(entry: Dict[str, Any]) -> str:
    """Resolve an {env, fallback[, subpath]} config entry to a concrete path."""
    value = os.environ.get(entry.get("env", "")) or entry.get("fallback", "")
    if entry.get("subpath"):
        value = str(Path(value) / entry["subpath"])
    return value


# ---------------------------------------------------------------------------
# Delink bootstrap + PE split
# ---------------------------------------------------------------------------


def get_delink_asset(delink_cfg: Dict[str, Any]) -> Tuple[str, str]:
    os_name = sys.platform
    arch = platform.machine().lower()

    if os_name == "win32":
        plat, asset_arch, ext, exec_name = "windows", "x86_64", ".exe", "delink.exe"
    elif os_name == "darwin":
        plat = "macos"
        asset_arch = "arm64" if ("arm" in arch or "aarch64" in arch) else "x86_64"
        ext, exec_name = "", "delink"
    elif os_name == "linux":
        plat, asset_arch, ext, exec_name = "linux", "x86_64", "", "delink"
    else:
        sys.exit(f"Unsupported platform: {os_name}")

    asset_name = delink_cfg["asset_name"].format(os=plat, arch=asset_arch, ext=ext)
    url = (
        f"https://github.com/{delink_cfg['repo']}/releases/download/"
        f"{delink_cfg['version']}/{asset_name}"
    )
    return url, exec_name


def bootstrap_delink(delink_cfg: Dict[str, Any], tools_dir: Path) -> Path:
    url, exec_name = get_delink_asset(delink_cfg)
    delink_path = tools_dir / exec_name

    if not delink_path.exists():
        print(f"[*] Downloading delink {delink_cfg['version']}...")
        tools_dir.mkdir(parents=True, exist_ok=True)
        try:
            urllib.request.urlretrieve(url, delink_path)
            if sys.platform != "win32":
                delink_path.chmod(0o755)
            print(f"[+] Downloaded to {delink_path}")
        except Exception as e:
            sys.exit(f"[-] Failed to download delink: {e}")

    return delink_path


def resolve_symbols_splits_paths(
    version: str, target_cfg: Dict[str, Any]
) -> Tuple[Path, Path, Path]:
    """(binary, symbols.txt, splits.txt) for this version, from `target:`."""
    binary = Path(target_cfg["binary"].format(version=version))
    symbols = Path(target_cfg["symbols"].format(version=version))
    splits = Path(target_cfg["splits"].format(version=version))
    return binary, symbols, splits


def build_convert_flags(ida_cfg: Dict[str, Any]) -> List[str]:
    """CLI flags forwarded to symbols_splits_to_json.py, sourced from the
    `target.ida:` block in config.yml (symbols.txt/splits.txt can't carry
    arch/bits/endian/filetype/image base themselves)."""
    flags: List[str] = []
    for key, flag in (
        ("arch", "--arch"),
        ("procname", "--procname"),
        ("bits", "--bits"),
        ("endian", "--endian"),
        ("filetype", "--filetype"),
        ("image_base", "--image-base"),
        ("input_file", "--input-file"),
    ):
        if key in ida_cfg:
            flags += [flag, str(ida_cfg[key])]
    return flags


def run_convert_and_split(
    delink_exe: Path,
    version: str,
    target_cfg: Dict[str, Any],
    base_build_dir: Path,
):
    """symbols.txt + splits.txt -> symbols.delink.json + idapro.json ->
    `delink ida-split`. Run once up front so the TU list (idapro.json) exists
    on a clean checkout; the same chain is also wired into build.ninja so
    editing symbols.txt/splits.txt and running `ninja` re-splits."""
    binary, symbols_txt, splits_txt = resolve_symbols_splits_paths(version, target_cfg)
    build_dir = base_build_dir / version
    out_obj_dir = build_dir / "obj"
    delink_json = build_dir / "symbols.delink.json"
    idapro_json = build_dir / "idapro.json"

    missing = [p for p in (binary, symbols_txt, splits_txt) if not p.exists()]
    if missing:
        print(
            f"[-] Warning: missing {', '.join(str(p) for p in missing)}. "
            f"Skipping split phase."
        )
        return

    build_dir.mkdir(parents=True, exist_ok=True)
    convert_script = Path(__file__).parent / "scripts" / "symbols_splits_to_json.py"

    print(f"[*] Converting {symbols_txt} + {splits_txt} -> {delink_json}...")
    convert_cmd = [
        sys.executable,
        str(convert_script),
        str(symbols_txt),
        str(splits_txt),
        str(delink_json),
        "--idapro-out",
        str(idapro_json),
    ] + build_convert_flags(target_cfg.get("ida", {}))
    result = subprocess.run(convert_cmd, capture_output=True, text=True)
    if result.returncode != 0:
        sys.exit(f"[-] symbols_splits_to_json.py failed:\n{result.stderr}")

    print(f"[*] Splitting {binary.name} via delink ida-split for {version}...")
    out_obj_dir.mkdir(parents=True, exist_ok=True)
    split_cmd = [
        str(delink_exe),
        "ida-split",
        "--outdir",
        str(out_obj_dir),
        "--idapro",
        str(idapro_json),
        "--coff",
        str(delink_json),
        str(binary),
    ]
    result = subprocess.run(split_cmd, capture_output=True, text=True)
    if result.returncode != 0:
        sys.exit(f"[-] delink ida-split failed:\n{result.stderr}")
    (out_obj_dir / ".split-stamp").touch()
    print("[+] ida-split successful.")


# ---------------------------------------------------------------------------
# Translation units (from idapro.json)
# ---------------------------------------------------------------------------
#
# A TU is an idapro.json key, i.e. a splits.txt file path with extension,
# e.g. "Popcap/Lawn/Zombie.cpp". delink writes each object to
# build/<version>/obj/<tu> verbatim (extension unchanged, so the delinked
# COFF for Zombie.cpp is obj/Popcap/Lawn/Zombie.cpp); a freshly compiled one
# lives at build/<version>/src/<tu with .obj>. There is no obj->source
# mapping in config.yml any more: renaming a TU means editing splits.txt.
#
# A TU only gets a compile edge if src/<tu> exists, so lib/* and unmapped/*
# TUs (no source yet) are objdiff target-only units.


def list_translation_units(idapro_json: Path) -> List[str]:
    if not idapro_json.exists():
        return []
    with open(idapro_json, encoding="utf-8") as f:
        return list(json.load(f).keys())


def has_source(tu: str) -> bool:
    return (Path("src") / tu).exists()


# ---------------------------------------------------------------------------
# Matching status (drives which obj gets linked per TU)
# ---------------------------------------------------------------------------
#
# "matching":    build/<version>/src/<tu>.obj  (freshly compiled)
# "nonmatching": build/<version>/obj/<tu>      (original delinked obj)
# Config-driven (link.status.matching: list of TU names) rather than inferred
# from what compiles. __shared_data.obj is always linked, never matchable.


def resolve_matching_status(tus: List[str], link_cfg: Dict[str, Any]) -> Dict[str, bool]:
    matching_list = link_cfg.get("status", {}).get("matching", [])
    unknown = [n for n in matching_list if n not in tus]
    if unknown:
        sys.exit(
            f"[-] link.status.matching references TU(s) not in idapro.json: "
            f"{unknown}. Names must match a splits.txt file key exactly, "
            f"extension included (e.g. 'Popcap/Lawn/Plant.cpp')."
        )
    matching_set = set(matching_list)
    return {tu: (tu in matching_set) for tu in tus}


def resolve_object_path(
    tu: str, is_matching: bool, version: str, base_build_dir: Path
) -> Path:
    build_dir = base_build_dir / version
    if is_matching:
        return build_dir / "src" / Path(tu).with_suffix(".obj")
    return build_dir / "obj" / tu


def resolve_per_file_flags(cfg: Dict[str, str], tu: str) -> str:
    """Directory keys (trailing '/') apply to everything under them, longest
    prefix first; an exact-file key (with or without extension) is appended
    after."""
    tu = tu.replace("\\", "/")
    parts: List[str] = []
    dirs = sorted((k for k in cfg if k.endswith("/") and tu.startswith(k)), key=len)
    parts += [cfg[k] for k in dirs]
    for k in (tu, str(Path(tu).with_suffix("")).replace("\\", "/")):
        if k in cfg:
            parts.append(cfg[k])
            break
    return " ".join(p.strip() for p in parts)


# ---------------------------------------------------------------------------
# MSVC8 toolchain bootstrap (portable, no Visual Studio install required)
# ---------------------------------------------------------------------------
#
# Mirrors what decomp.me's own MSVC8 compiler Docker image does: fetch
# widberg/msvc8.0 (a portable extraction of VS2005/VC80), lay bin/ and
# include/ (+ PlatformSDK/Include) into a flat Bin/Include, and use that
# directly -- no installer, no registry, no vcvarsall.bat needed, and it
# works identically on Windows, Linux, and macOS. On non-Windows hosts,
# `wibo` (a minimal cli-only Windows binary runner) is also bootstrapped
# and used to invoke cl.exe/link.exe.


def toolchain_dir_from_env(compiler_cfg: Dict[str, Any]) -> Optional[Path]:
    """A contributor-supplied toolchain root always wins over downloading
    one. Expected layout: <dir>/Bin, <dir>/Include, optionally <dir>/Lib.
    """
    toolchain_cfg = compiler_cfg.get("toolchain", {})
    env_val = os.environ.get(toolchain_cfg.get("env", ""))
    if env_val:
        env_path = Path(env_val)
        if env_path.is_dir():
            return env_path
        print(
            f"[-] Warning: {toolchain_cfg['env']} is set to '{env_val}' but "
            f"that path doesn't exist. Falling back to the bootstrapped "
            f"toolchain instead."
        )
    return None


def bootstrap_msvc8_toolchain(compiler_cfg: Dict[str, Any], tools_dir: Path) -> Path:
    """Downloads+lays out widberg/msvc8.0 exactly like decomp.me's own
    MSVC8 Dockerfile does, so Bin/ and Include/ end up flat (PlatformSDK's
    Include merged straight into Include/) and reusable across versions.
    Returns the toolchain root (containing Bin/, Include/, Lib/).
    """
    env_dir = toolchain_dir_from_env(compiler_cfg)
    if env_dir is not None:
        print(f"[*] Using user-supplied MSVC8 toolchain at {env_dir}")
        return env_dir

    toolchain_cfg = compiler_cfg["toolchain"]
    repo = toolchain_cfg["repo"]
    ref = toolchain_cfg["ref"]

    toolchain_root = tools_dir / "msvc8.0"
    marker = toolchain_root / ".bootstrap-complete"
    if marker.exists() and marker.read_text().strip() == ref:
        return toolchain_root

    print(f"[*] Bootstrapping portable MSVC8 toolchain from {repo}@{ref[:12]}...")
    tools_dir.mkdir(parents=True, exist_ok=True)
    zip_path = tools_dir / f"{ref}.zip"
    url = f"https://github.com/{repo}/archive/{ref}.zip"

    try:
        if not zip_path.exists():
            print(f"[*] Downloading {url}...")
            urllib.request.urlretrieve(url, zip_path)

        extract_dir = tools_dir / f"_msvc8_extract_{ref[:12]}"
        if extract_dir.exists():
            shutil.rmtree(extract_dir)
        print("[*] Extracting archive...")
        with zipfile.ZipFile(zip_path) as zf:
            zf.extractall(extract_dir)

        # Archive unpacks to a single "<repo>-<ref>" subdirectory.
        src_roots = list(extract_dir.glob("msvc8.0-*"))
        if not src_roots:
            sys.exit(f"[-] Unexpected archive layout in {extract_dir}")
        src_root = src_roots[0]

        if toolchain_root.exists():
            shutil.rmtree(toolchain_root)
        bin_dir = toolchain_root / "Bin"
        include_dir = toolchain_root / "Include"
        lib_dir = toolchain_root / "Lib"
        bin_dir.mkdir(parents=True)
        include_dir.mkdir(parents=True)
        lib_dir.mkdir(parents=True)

        # Same three copies the Dockerfile does, plus Lib (needed here
        # since, unlike decomp.me's scratch compiles, this workflow also
        # links a full .exe).
        _copytree_merge(src_root / "bin", bin_dir)
        _copytree_merge(src_root / "include", include_dir)
        _copytree_merge(src_root / "PlatformSDK" / "Include", include_dir)
        if (src_root / "lib").is_dir():
            _copytree_merge(src_root / "lib", lib_dir)
        if (src_root / "PlatformSDK" / "Lib").is_dir():
            _copytree_merge(src_root / "PlatformSDK" / "Lib", lib_dir)

        if sys.platform != "win32":
            for exe in bin_dir.glob("*"):
                if exe.is_file():
                    exe.chmod(
                        exe.stat().st_mode | stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH
                    )

        shutil.rmtree(extract_dir)
        zip_path.unlink()
        marker.write_text(ref)
        print(f"[+] MSVC8 toolchain ready at {toolchain_root}")
    except Exception as e:
        sys.exit(f"[-] Failed to bootstrap MSVC8 toolchain: {e}")

    return toolchain_root


def _copytree_merge(src: Path, dst: Path) -> None:
    """shutil.copytree with dirs_exist_ok, but tolerant of a missing src
    (some toolchain archives may not ship a Lib dir, etc.)."""
    if not src.is_dir():
        return
    shutil.copytree(src, dst, dirs_exist_ok=True)


WIBO_REPO = "decompals/wibo"
WIBO_TAG = "1.2.0"


def bootstrap_wibo(tools_dir: Path) -> Optional[Path]:
    """Downloads decompals/wibo, the same lightweight cli-only Windows
    binary runner decomp.me itself uses, so cl.exe/link.exe can run
    on Linux/macOS without Wine. Returns None on win32 (not needed).
    """
    if sys.platform == "win32":
        return None

    machine = platform.machine().lower()
    if sys.platform == "darwin":
        asset = "wibo-macos"
    elif "aarch64" in machine or "arm64" in machine:
        # wibo has no native arm64 Linux build; only x86/x86_64 static
        # binaries are published. On arm64 Linux, either run under an
        # x86_64 chroot/emulation layer that provides wibo-x86_64, or
        # install real Wine and adapt this function to shell out to it.
        sys.exit(
            "[-] No prebuilt wibo binary for arm64 Linux. Install Wine "
            "and adapt bootstrap_wibo(), or run this under x86_64 "
            "emulation."
        )
    elif "64" in machine:
        asset = "wibo-x86_64"
    else:
        asset = "wibo-i686"

    wibo_path = tools_dir / "wibo"
    if wibo_path.exists():
        return wibo_path

    tools_dir.mkdir(parents=True, exist_ok=True)
    url = f"https://github.com/{WIBO_REPO}/releases/download/{WIBO_TAG}/{asset}"
    print(f"[*] Downloading wibo ({asset})...")
    try:
        urllib.request.urlretrieve(url, wibo_path)
        wibo_path.chmod(
            wibo_path.stat().st_mode | stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH
        )
        print(f"[+] Downloaded wibo to {wibo_path}")
    except Exception as e:
        sys.exit(f"[-] Failed to download wibo: {e}")

    return wibo_path


def get_compiler_environment(
    compiler_cfg: Dict[str, Any], tools_dir: Path
) -> Tuple[Path, Optional[Path], list]:
    """Resolves (and bootstraps, if needed) the MSVC8 toolchain root, the
    wibo wrapper binary (non-Windows only, else None), and extra include
    dirs (e.g. DXSDK, which is not auto-downloaded -- see config.yml).
    """
    toolchain_root = bootstrap_msvc8_toolchain(compiler_cfg, tools_dir)
    wibo_path = bootstrap_wibo(tools_dir)

    extra_includes = [
        resolve_env_path(entry) for entry in compiler_cfg.get("extra_includes", [])
    ]
    missing_dx = [d for d in extra_includes if d and not Path(d).is_dir()]
    if missing_dx:
        print(
            f"[-] Warning: DirectX SDK include dir(s) not found: {missing_dx}. "
            f"Set DXSDK_DIR to your DirectX SDK (June 2010) install, or "
            f"compiles that need d3d8.h/ddraw.h/dsound.h will fail."
        )

    return toolchain_root, wibo_path, extra_includes


def build_include_flags(
    compiler_cfg: Dict[str, Any], toolchain_root: Path, extra_includes: list
) -> str:
    dirs = (
        [str((toolchain_root / "Include").resolve())]
        + extra_includes
        + [str(Path(d).resolve()) for d in compiler_cfg.get("include_dirs", [])]
    )
    return " ".join(f'/I"{d}"' for d in dirs)


def resolve_link_lib_dirs(link_cfg: Dict[str, Any], toolchain_root: Path) -> list:
    """Resolve link.lib_dirs {env, fallback[, subpath]} entries to paths,
    plus the bootstrapped MSVC8 toolchain's own Lib dir (user32.lib,
    gdi32.lib, etc. -- from widberg/msvc8.0's copy of the Platform SDK),
    which isn't hardcoded in config.yml since its location depends on
    where the toolchain was bootstrapped on this machine.
    """
    configured = [resolve_env_path(entry) for entry in link_cfg.get("lib_dirs", [])]
    return [str((toolchain_root / "Lib").resolve())] + configured


def verify_link_libs(link_cfg: Dict[str, Any], lib_dirs: list) -> None:
    """Check every entry in link.libs actually resolves under one of
    lib_dirs (or is a bare name the linker will find via its own default
    library search, e.g. user32.lib/gdi32.lib from the bootstrapped
    toolchain's own Lib dir, which resolve_link_lib_dirs() always
    includes). This exists because a missing import lib (e.g. ddraw.lib
    not shipping in a given DXSDK release) otherwise
    only surfaces as an opaque 'LINK : fatal error LNK1181: cannot open
    input file' after every object has already compiled -- expensive to
    discover late in a multi-minute build. We can only check paths that
    are actually reachable from wherever configure.py is running (e.g. a
    Windows checkout, or a mapped drive); if a lib_dir doesn't exist at
    all here, we skip it silently rather than false-alarm on an
    environment mismatch (this script may be generating the ninja file
    from a different machine/OS than the one that will run ninja).
    """
    libs = link_cfg.get("libs", [])
    if not libs or not lib_dirs:
        return

    existing_dirs = [d for d in lib_dirs if Path(d).is_dir()]
    if not existing_dirs:
        # None of the configured lib_dirs are visible from here -- can't
        # verify anything, and that's fine (likely cross-machine/cross-OS
        # config generation). Stay silent rather than false-alarm.
        return

    missing = []
    for lib in libs:
        found = any((Path(d) / lib).is_file() for d in existing_dirs)
        if not found:
            missing.append(lib)

    if missing:
        dirs_str = "\n".join(f"    {d}" for d in existing_dirs)
        libs_str = ", ".join(missing)
        print(
            f"[-] Warning: the following libs in link.libs were not found "
            f"under any configured link.lib_dirs:\n{dirs_str}\n"
            f"    Missing: {libs_str}\n"
            f"    (They may still resolve via the linker's own default "
            f"search path from vcvarsall, but if not, this is why link.exe "
            f"would fail with LNK1181.)"
        )


def build_link_flags(link_cfg: Dict[str, Any], lib_dirs: list) -> str:
    """Builds the full /link.exe flag string from the `link:` config block."""
    subsystem = link_cfg.get("subsystem", "windows").upper()
    is_dll = link_cfg.get("target", "exe") == "dll"

    parts = [
        "/NOLOGO",
        f"/SUBSYSTEM:{subsystem}",
    ]
    if is_dll:
        parts.append("/DLL")

    base_address = link_cfg.get("base_address")
    if base_address:
        parts.append(f"/BASE:{base_address}")

    stack_reserve = link_cfg.get("stack_reserve")
    stack_commit = link_cfg.get("stack_commit")
    if stack_reserve:
        stack = f"/STACK:{stack_reserve}"
        if stack_commit:
            stack += f",{stack_commit}"
        parts.append(stack)

    for lib_dir in lib_dirs:
        parts.append(f'/LIBPATH:"{lib_dir}"')

    extra_flags = link_cfg.get("extra_flags", "")
    if extra_flags:
        parts.append(extra_flags)

    libs = link_cfg.get("libs", [])
    parts.extend(libs)

    return " ".join(str(p) for p in parts if p)


# ---------------------------------------------------------------------------
# Ninja generation
# ---------------------------------------------------------------------------


def build_tool_prefix(wibo_path: Optional[Path]) -> str:
    """Prefix used to invoke a Windows .exe tool: nothing on Windows,
    `wibo <path>` everywhere else. Kept as its own helper since both the
    cxx and link rules need it identically.
    """
    if wibo_path is None:
        return ""
    return f'"{wibo_path.resolve()}" '


def generate_ninja_build(
    version: str,
    tus: List[str],
    base_build_dir: Path,
    compiler_cfg: Dict[str, Any],
    toolchain_root: Path,
    wibo_path: Optional[Path],
    extra_includes: list,
    delink_exe: Path,
    target_cfg: Dict[str, Any],
    link_cfg: Optional[Dict[str, Any]] = None,
    matching_status: Optional[Dict[str, bool]] = None,
    link_lib_dirs: Optional[list] = None,
):
    build_dir = base_build_dir / version
    ninja_file = Path("build.ninja")

    print(f"[*] Generating {ninja_file}...")

    include_flags = build_include_flags(compiler_cfg, toolchain_root, extra_includes)
    base_flags = f"{compiler_cfg['base_flags']} {include_flags}"

    cl_exe = (toolchain_root / "Bin" / "cl.exe").resolve()
    link_exe = (toolchain_root / "Bin" / "link.exe").resolve()
    tool_prefix = build_tool_prefix(wibo_path)

    binary, symbols_txt, splits_txt = resolve_symbols_splits_paths(version, target_cfg)
    delink_json = build_dir / "symbols.delink.json"
    idapro_json = build_dir / "idapro.json"
    convert_script = (Path(__file__).parent / "scripts" / "symbols_splits_to_json.py").resolve()
    split_stamp = build_dir / "obj" / ".split-stamp"
    convert_flags = " ".join(build_convert_flags(target_cfg.get("ida", {})))

    pch_cfg: Optional[Dict[str, Any]] = compiler_cfg.get("pch")
    pch_file = pch_obj = precompile_cpp = None
    pch_flags = ""

    if pch_cfg:
        pch_file = build_dir / "src" / pch_cfg["output"]
        precompile_cpp = Path(pch_cfg["source"])
        pch_obj = (build_dir / "src" / precompile_cpp.relative_to("src")).with_suffix(
            ".obj"
        )
        pch_flags = (
            f"{pch_cfg['flags']} {include_flags} "
            f'/Yc{pch_cfg["header"]} /Fp"{pch_file.resolve()}"'
        )

    with open(ninja_file, "w") as f:
        f.write("# Generated by configure.py automatically. Do not edit.\n\n")
        f.write("ninja_required_version = 1.3\n\n")

        f.write(f"base_flags = {base_flags}\n\n")

        # --- Split step ----------------------------------------------------
        # symbols.txt + splits.txt -> JSON -> delink ida-split. ida-split's
        # output set (one obj per splits.txt file) isn't known ahead of time,
        # so the split is tracked through a stamp file that everything
        # consuming the delinked objs depends on.
        f.write("rule convert_json\n")
        f.write(
            f'  command = "{sys.executable}" "{convert_script}" $symbols $splits '
            f"$out --idapro-out $idapro_out {convert_flags}\n"
        )
        f.write("  description = CONVERT $out\n\n")
        f.write(f"build {delink_json} | {idapro_json}: convert_json {symbols_txt} {splits_txt}\n")
        f.write(f"  symbols = {symbols_txt}\n  splits = {splits_txt}\n")
        f.write(f"  idapro_out = {idapro_json}\n\n")

        run_split = (Path(__file__).parent / "scripts" / "run_split.py").resolve()
        f.write("rule ida_split\n")
        f.write(
            f'  command = "{sys.executable}" "{run_split}" $out '
            f'"{delink_exe.resolve()}" ida-split --outdir $outdir '
            f"--idapro $idapro --coff $in $binary\n"
        )
        f.write("  description = IDA-SPLIT $in\n\n")
        f.write(f"build {split_stamp}: ida_split {delink_json} | {idapro_json} {binary}\n")
        f.write(f"  outdir = {build_dir / 'obj'}\n")
        f.write(f"  idapro = {idapro_json}\n")
        f.write(f"  binary = {binary}\n\n")

        # No cmd.exe / vcvarsall.bat: the bootstrapped MSVC8 toolchain is
        # portable, so cl.exe/link.exe are invoked directly by absolute path.
        # On non-Windows, `wibo` runs them without needing Wine.
        f.write("rule cxx\n")
        f.write(
            f'  command = {tool_prefix}"{cl_exe}" /c $in /Fo$out '
            "$base_flags $per_file_flags\n"
        )
        f.write("  description = CXX $in\n\n")

        if pch_cfg:
            f.write("rule make_pch\n")
            f.write(
                f'  command = {tool_prefix}"{cl_exe}" /c $in /Fo$obj_out $pch_flags\n'
            )
            f.write("  description = PCH $in\n\n")

            if precompile_cpp.exists():
                pch_obj.parent.mkdir(parents=True, exist_ok=True)
                f.write(f"build {pch_obj} | {pch_file}: make_pch {precompile_cpp}\n")
                f.write(f"  pch_flags = {pch_flags}\n  obj_out = {pch_obj}\n\n")

        per_file_flags_cfg = compiler_cfg.get("per_file_flags", {})

        for tu in tus:
            if not has_source(tu):
                continue
            src_file = Path("src") / tu
            out_obj = build_dir / "src" / Path(tu).with_suffix(".obj")

            per_file_flags = resolve_per_file_flags(per_file_flags_cfg, tu)
            if per_file_flags and pch_file is not None:
                per_file_flags = per_file_flags.format(
                    pch_path=f'"{pch_file.resolve()}"'
                )

            implicit_deps = ""
            if pch_cfg and "/Yu" in per_file_flags and precompile_cpp.exists():
                implicit_deps = f" | {pch_file}"

            f.write(f"build {out_obj}: cxx {src_file}{implicit_deps}\n")
            if per_file_flags:
                f.write(f"  per_file_flags = {per_file_flags}\n")

        # --- Link step ---------------------------------------------------
        # Matching TUs link from build/<version>/src; nonmatching ones link
        # the delinked obj, which the split stamp (re)produces, so they get
        # an order-only-ish implicit dep on it. __shared_data.obj (delink's
        # catch-all for data/bss) is always linked.
        if link_cfg is not None and matching_status is not None:
            link_flags = build_link_flags(link_cfg, link_lib_dirs or [])
            output_exe = build_dir / link_cfg.get("output", "output.exe")
            map_file = output_exe.with_suffix(".map")

            f.write(f"link_flags = {link_flags}\n\n")
            f.write("rule link\n")
            f.write(
                f'  command = {tool_prefix}"{link_exe}" $in /OUT:$out $link_flags\n'
            )
            f.write("  description = LINK $out\n\n")

            link_inputs = []
            for tu in tus:
                link_inputs.append(
                    str(
                        resolve_object_path(
                            tu, matching_status.get(tu, False), version, base_build_dir
                        )
                    )
                )
            link_inputs.append(str(build_dir / "obj" / "__shared_data.obj"))

            f.write(
                f"build {output_exe} | {map_file}: link {' '.join(link_inputs)} "
                f"| {split_stamp}\n"
            )


# ---------------------------------------------------------------------------
# objdiff.json generation
# ---------------------------------------------------------------------------


def generate_objdiff_config(
    version: str,
    tus: List[str],
    base_build_dir: Path,
    compiler_cfg: Dict[str, Any],
    toolchain_root: Path,
    objdiff_cfg: Dict[str, Any],
    extra_includes: list,
):
    objdiff_path = Path("objdiff.json")
    build_dir = base_build_dir / version

    print(f"[*] Generating {objdiff_path}...")

    include_flags = build_include_flags(compiler_cfg, toolchain_root, extra_includes)
    base_flags = f"{compiler_cfg['base_flags']} {include_flags}"

    pch_cfg: Optional[Dict[str, Any]] = compiler_cfg.get("pch")
    pch_file = build_dir / "src" / pch_cfg["output"] if pch_cfg else None
    per_file_flags_cfg = compiler_cfg.get("per_file_flags", {})
    unit_prefix = objdiff_cfg.get("unit_prefix", "main")
    categories = objdiff_cfg.get("progress_categories", [])

    units = []
    n_src = 0
    for tu in tus:
        tu_path = Path(tu)
        unit_name = f"{unit_prefix}/{tu_path.with_suffix('')}".replace("\\", "/")
        target_path = build_dir / "obj" / tu

        if not has_source(tu):
            units.append(
                {
                    "name": unit_name,
                    "target_path": str(target_path).replace("\\", "/"),
                    "base_path": None,
                    "metadata": {
                        "complete": False,
                        "reverse_fn_order": False,
                        "progress_categories": categories,
                        "auto_generated": False,
                    },
                }
            )
            continue

        n_src += 1
        base_path = build_dir / "src" / tu_path.with_suffix(".obj")
        ctx_path = build_dir / "src" / tu_path.with_suffix(".ctx")

        per_file_flags = resolve_per_file_flags(per_file_flags_cfg, tu)
        if per_file_flags and pch_file is not None:
            per_file_flags = per_file_flags.format(
                pch_path=str(pch_file).replace("\\", "/")
            )
        combined_flags = f"{base_flags} {per_file_flags}".strip()

        units.append(
            {
                "name": unit_name,
                "target_path": str(target_path).replace("\\", "/"),
                "base_path": str(base_path).replace("\\", "/"),
                "scratch": {
                    "platform": "windows",
                    "compiler": "cl.exe",
                    "c_flags": combined_flags,
                    "ctx_path": str(ctx_path).replace("\\", "/"),
                    "build_ctx": False,
                },
                "metadata": {
                    "complete": False,
                    "reverse_fn_order": False,
                    "source_path": f"src/{tu}".replace("\\", "/"),
                    "progress_categories": categories,
                    "auto_generated": False,
                },
            }
        )

    print(
        f"[*] {n_src} TU(s) with source, {len(units) - n_src} target-only "
        f"(lib/unmapped -- no source yet)."
    )

    config_data = {
        "min_version": objdiff_cfg.get("min_version", "2.0.0-beta.5"),
        "custom_make": "ninja",
        "build_target": False,
        "watch_patterns": objdiff_cfg.get("watch_patterns", []),
        "units": units,
    }

    with open(objdiff_path, "w") as f:
        json.dump(config_data, f, indent=2)


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------


def main():
    config_root = Path("config")
    available_versions = discover_versions(config_root)

    parser = argparse.ArgumentParser(
        description="Configure implementation for PE-based decompilation workflows."
    )
    parser.add_argument(
        "-v",
        "--version",
        choices=available_versions or None,
        default=available_versions[0] if available_versions else None,
        help="Target game version",
    )
    parser.add_argument(
        "--analyze",
        metavar="VERSION",
        help="(Re)generate config/VERSION/{symbols,splits}.txt from orig/VERSION/ "
        "(.exe required; .map/.pdb optional) and exit. Creates config/VERSION/"
        "config.yml if the version is new. Existing files are kept as *.bak.",
    )
    parser.add_argument(
        "--template",
        metavar="VERSION",
        help="With --analyze on a new version: clone config.yml from this existing "
        "version instead of using the built-in generic template.",
    )
    parser.add_argument(
        "--build-dir",
        type=Path,
        default=Path("build"),
        help="Base output build directory",
    )
    args = parser.parse_args()

    if args.analyze:
        sys.path.insert(0, str(Path(__file__).parent / "scripts"))
        from analyze import analyze_version

        analyze_version(args.analyze, config_root, Path("orig"), Path("src"), template=args.template)
        return

    if not args.version:
        sys.exit("[-] No versions found under config/. Put the binary in orig/<NAME>/ and run: python configure.py --analyze <NAME>")
    cfg = load_config(config_root, args.version)

    tools_dir = args.build_dir / "tools"
    delink_exe = bootstrap_delink(cfg["delink"], tools_dir)

    # 1. symbols.txt + splits.txt -> JSON -> ida-split
    run_convert_and_split(delink_exe, args.version, cfg["target"], args.build_dir)

    # 2. TUs come straight from idapro.json (splits.txt's file keys)
    idapro_json = args.build_dir / args.version / "idapro.json"
    tus = list_translation_units(idapro_json)

    if not tus:
        print("[-] No TUs found (idapro.json missing/empty) -- nothing to configure.")
        return

    # 3. Toolchain. On a clean clone this downloads a portable MSVC8 (+ wibo
    # on non-Windows) into build/tools/; no Visual Studio install needed.
    compiler_cfg = cfg["compiler"]
    toolchain_root, wibo_path, extra_includes = get_compiler_environment(
        compiler_cfg, tools_dir
    )

    # 3b. Optional relink config + per-TU matching status.
    link_cfg = cfg.get("link")
    if link_cfg is not None and not link_cfg.get("enabled", True):
        print(
            "[*] Relinking disabled (link.enabled: false in config.yml) "
            "-- generating compile-only ninja/objdiff configs."
        )
        link_cfg = None
    matching_status = None
    link_lib_dirs = None
    if link_cfg is not None:
        matching_status = resolve_matching_status(tus, link_cfg)
        link_lib_dirs = resolve_link_lib_dirs(link_cfg, toolchain_root)
        verify_link_libs(link_cfg, link_lib_dirs)
        n_matching = sum(matching_status.values())
        print(
            f"[*] Matching status: {n_matching}/{len(matching_status)} TUs marked "
            f"matching (rest linked from original delinked objs)."
        )

    # 4. Build scripts
    generate_ninja_build(
        args.version,
        tus,
        args.build_dir,
        compiler_cfg,
        toolchain_root,
        wibo_path,
        extra_includes,
        delink_exe,
        cfg["target"],
        link_cfg=link_cfg,
        matching_status=matching_status,
        link_lib_dirs=link_lib_dirs,
    )
    generate_objdiff_config(
        args.version,
        tus,
        args.build_dir,
        compiler_cfg,
        toolchain_root,
        cfg.get("objdiff", {}),
        extra_includes,
    )


if __name__ == "__main__":
    main()

# Plants vs. Zombies Decompilation

A work-in-progress decompilation of the 0.9.9 beta build of Plants vs. Zombies.

## Requirements

- Python 3.9+ with [`pyyaml`](https://pypi.org/project/PyYAML/) (`pip install pyyaml`)
- [Ninja](https://ninja-build.org/)
- Your own copy of `PlantsVsZombies.exe` and `PlantsVsZombies.pdb`
- [objdiff](https://github.com/encounter/objdiff)

Automatically installed will be:

- [delink](https://github.com/HaydnTrigg/delink)
- [wibo](https://github.com/decompals/wibo) (on non-Windows platforms)
- MSVC 8.0 (from [widberg/msvc8.0](https://github.com/widberg/msvc8.0))

## Building

1. Copy `PlantsVsZombies.exe` and `PlantsVsZombies.pdb` into `orig/BETA_099/`
2. Run `python configure.py`
3. Run `ninja`

Set `DXSDK_DIR` if your DirectX SDK isn't at the default path, and `MSVC8_DIR`
to use your own MSVC8/VC80 install instead of the bootstrapped one.

## Contributing

Open the repo root in [objdiff](https://github.com/encounter/objdiff) to see
per-TU match progress.

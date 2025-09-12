# Plants vs. Zombies (0.9.9) Decompilation

A very messy incomplete repo based on [th06](https://github.com/happyhavoc/th06)

In order to set it up you're gonna have to delink the program in ghidra using `scripts/ghidra/ExportDelinker.py` with the [ghidra-delinker-extension](https://github.com/boricj/ghidra-delinker-extension) and `config/ghidra_ns_to_obj.csv` to get all the .obj files delinked into `build/orig/`. You will also need Microsoft Visual Studio 2005 (or 8.0) to build.

A lot of stuff is leftover from th06 because I haven't bothered cleaning it up. An attempt was made with pvz_vars.bat but right now the build.py is hardcoded to a specific path for MSVC anyway. There's not even proper automatic configuration of the objdiff.json. Again, this is a very messy WIP repo.
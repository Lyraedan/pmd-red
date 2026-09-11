# Pokémon Mystery Dungeon: Red Rescue Team

[![build](https://github.com/pret/pmd-red/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/pret/pmd-red/actions/workflows/build.yml)

This is a decompilation of Pokémon Mystery Dungeon: Red Rescue Team.

It builds the following rom:

* pmd_red.gba `sha1: 9f4cfc5b5f4859d17169a485462e977c7aac2b89`

To set up the repository, see [INSTALL.md](INSTALL.md).

For contacts and other pret projects, see [pret.github.io](https://pret.github.io/).

# PC Port

To build, 
First run @git submodule update --init --recursive to fetch the latest imgui version.
Place your US rom of Red Rescue Team in the root of the repo, then run "builder/win_rebuild.bat" to build. (Tested only on x86_64 intel)
The exe will be built and staged in "build"
Uses msys2 to build and assumes that is in C:

Uses SDL2 for rendering & audio
Nothing is emulated, everything runs natively.
Saves are compatible with emulator saves. Just copy your .sav to the directory of the exe and rename it to "rescue-team.sav"

You'll need python for asset generation (graphics, sfx etc)

If you have everything it will build successfully and it will copy the rom into build during staging.

## Don't want to build it yourself?
There is a built exe in the release page of this repo.

# AI Notice
I did use AI to assist the creation of this PC port as the decomp this is a fork of is incomplete and there are alot of "stub" and obfuscated function and variable names.

# Moonwright

Moonwright is a standalone Harvest Moon 64 PC port project.

This repository is the port, not the original decomp repository. The target model is the same philosophy used by Shipwright and SpaghettiKart: keep the real game startup, callback flow, and main loop in charge, and build the port around that instead of replacing it with a fake frontend or preview runtime.

## Goals

- Boot through the real HM64 startup path.
- Keep `mainproc() -> setupGameStart() -> mainLoop()` as the runtime owner path.
- Use packaged archive assets through `OTRExporter` and `libultraship`.
- Keep port-specific code in `hm64/moonwright` and imported game code in `hm64/src` and `hm64/include`.
- Follow Shipwright and SpaghettiKart as the reference model for structure and runtime philosophy.

## Current Status

Current verified state:

- `Release`, `RelWithDebInfo`, and `Debug` build through CMake presets.
- The real intro and logo sequence runs through the real game logic path.
- The funeral outdoor scene now loads.
- Dialogue portrait, window, and text render on screen.
- The runtime is using the real HM64 startup path instead of any preview or test runtime.

The port is still in active development. Reaching the title screen and stable gameplay end-to-end remains ongoing work.

## Repository Layout

```text
Moonwright/
|- CMakeLists.txt
|- CMakePresets.json
|- README.md
|- .gitmodules
|- hm64.json
|- CMake/
|- hm64/
|  |- CMakeLists.txt
|  |- assets/
|  |- include/
|  |- src/
|  |- tools/
|  `- moonwright/
|     |- include/
|     `- src/
|- libultraship/
`- OTRExporter/
```

Important ownership split:

- `hm64/src` and `hm64/include`
  Imported HM64 game source and headers.
- `hm64/moonwright/src` and `hm64/moonwright/include`
  Port-owned runtime, platform, renderer, and host integration code.
- `libultraship`
  Rendering, windowing, archive/resource, and platform support.
- `OTRExporter`
  Build-time archive/export pipeline.

## Submodules

Moonwright uses Git submodules for external dependencies:

- `libultraship`
- `OTRExporter`

Clone with submodules:

```bash
git clone --recurse-submodules git@github.com:JamesAnthonyDellaMorte/Moonwright.git
cd Moonwright
```

If you already cloned:

```bash
git submodule update --init --recursive
```

## Prerequisites

macOS dependencies:

```bash
brew install cmake ninja sdl2 glew libzip tinyxml2 nlohmann-json
```

Moonwright does not ship a ROM. You are expected to provide your own legal game data and build inputs outside the repository.

## Building

Moonwright uses CMake presets directly.

```bash
cmake --preset release
cmake --build --preset release

cmake --preset relwithdeb
cmake --build --preset relwithdeb

cmake --preset debug
cmake --build --preset debug
```

Build directories:

```text
build             Release
build-relwithdeb  RelWithDebInfo
build-debug       Debug
```

Executable paths:

```text
build/bin/Moonwright.app/Contents/MacOS/Moonwright
build-relwithdeb/bin/Moonwright.app/Contents/MacOS/Moonwright
build-debug/bin/Moonwright-debug.app/Contents/MacOS/Moonwright-debug
```

## Running

Run the normal binary:

```bash
./build/bin/Moonwright.app/Contents/MacOS/Moonwright
```

Run the debug binary:

```bash
./build-debug/bin/Moonwright-debug.app/Contents/MacOS/Moonwright-debug
```

Launch LLDB MCP for the debug binary:

```bash
./launch-lldb-debug.sh
```

## Asset Flow

Moonwright uses a Shipwright-style packaged asset path:

- build-time export through `OTRExporter`
- packaged archive generation into `Moonwright.o2r`
- runtime archive mounting through `libultraship`

The current port still bridges some imported HM64 runtime systems through host-side compatibility code where necessary, but the direction is to keep moving toward archive-owned runtime asset flow instead of one-off Moonwright-only workarounds.

## Runtime Philosophy

These rules are intentional and non-optional:

- no fake asset viewer
- no preview launcher
- no alternate runtime owner path
- no replacing the real game startup with a test harness

The active executable must stay on the real HM64 startup and loop path. If a system is incomplete, trim leaf behavior only. Do not replace the real owner path.

## Golden References

Moonwright uses these projects as the decision model:

- Shipwright
- SpaghettiKart

If there is doubt about structure, build ownership, runtime flow, or asset policy, match those projects rather than inventing a Moonwright-only detour.

## Notes

- `build.sh` is not the primary build system. Use the CMake presets.
- `rom_symbols.c` stays deleted.
- giant fake symbol bridges are not the intended direction.
- `libultraship` should only be changed for real generic library bugs, not HM64-specific integration mistakes.

## License

Moonwright follows the licensing model of the HM64 decomp project it is derived from.

`libultraship` is a separate dependency with its own license terms.

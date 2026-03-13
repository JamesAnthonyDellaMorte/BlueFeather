# BlueFeather

BlueFeather is a work-in-progress native PC port of Harvest Moon 64.

> [!WARNING]
> BlueFeather is currently a proof-of-concept port. The full intro sequence works, audio is up, and the early flow is running with only very minor graphics issues in that path, but the project is not yet fully playable. Expect missing systems, bugs, visual issues, audio issues, and breaking changes while development continues.

## Current Status

BlueFeather is still in active early development. The project is focused on bringing up a clean native PC port architecture, archive-backed assets, host-driven timing, host audio playback, and basic debugging tools before it is treated as a complete game port. The port currently gets through the full intro sequence and into early game flow, with only minor graphics issues remaining in the intro/title path.

At the moment, BlueFeather should be treated as a development snapshot rather than a finished way to play Harvest Moon 64.

BlueFeather does not include copyrighted game assets. You are required to provide a supported Harvest Moon 64 ROM.

# Quick Start

### 1. Clone the repository and submodules

```bash
git clone --recurse-submodules git@github.com:JamesAnthonyDellaMorte/BlueFeather.git BlueFeather
cd BlueFeather
```

If you already cloned the repo:

```bash
git submodule update --init --recursive
```

### 2. Verify your ROM is in `.z64` format

BlueFeather expects a big-endian `.z64` ROM. If your dump is in `.n64` format, convert it before continuing.

### 3. Place your ROM in the repository root

Put your supported ROM at:

```text
./baserom.us.z64
```

BlueFeather's Torch metadata is repo-owned, and the base archive is generated directly from this ROM in the same way the Harbour Masters golden repos generate their base archives.

### 4. Install prerequisites

macOS dependencies:

```bash
brew install cmake ninja python sdl2 glew libzip tinyxml2 nlohmann-json
```

### 5. Build BlueFeather

```bash
cmake --preset debug
cmake --build --preset debug
```

Other supported presets:

```bash
cmake --preset release
cmake --build --preset release

cmake --preset relwithdeb
cmake --build --preset relwithdeb
```

### 6. Generate the asset archives

BlueFeather follows the Harbour Masters pattern:

- `hm64.o2r` is generated from `baserom.us.z64` through Torch
- `BlueFeather.o2r` is packed from the repo-owned `port/` asset tree

This two-archive layout is intentional and matches the Harbour Masters ports:

- base archive: the original game data converted from the ROM
- port archive: BlueFeather-owned shaders and other port-specific assets

That is the same model used by the golden repos:

- `mk64.o2r` + `spaghetti.o2r`
- `sf64.o2r` + `starship.o2r`

Generate both archives with:

```bash
cmake --build --preset debug --target ExtractAssets
```

You can also generate them individually:

```bash
cmake --build --preset debug --target GenerateHm64Otr
cmake --build --preset debug --target GenerateBlueFeatherOtr
```

### 7. Launch the game

Debug build:

```bash
./build-debug/bin/BlueFeather-debug.app/Contents/MacOS/BlueFeather-debug
```

Release build:

```bash
./build/bin/BlueFeather.app/Contents/MacOS/BlueFeather
```

# Build Output

BlueFeather's normal executable build and asset extraction are separate, matching the Harbour Masters repos:

- `cmake --build --preset debug` builds the app
- `cmake --build --preset debug --target ExtractAssets` generates:
  - `hm64.o2r`
  - `BlueFeather.o2r`

The generated archives are copied into the build directory. On macOS, helper targets are also available to copy them into the app bundle resources if you want to run directly from the bundle.

When you run `ExtractAssets`, BlueFeather stages the archives where the app expects them by default:

- `build-debug/bin/hm64.o2r`
- `build-debug/bin/BlueFeather.o2r`
- `build-debug/bin/BlueFeather-debug.app/Contents/Resources/hm64.o2r`
- `build-debug/bin/BlueFeather-debug.app/Contents/Resources/BlueFeather.o2r`

This mirrors the Harbour Masters pattern: build the app separately, then generate and stage the archives for the runtime location the app already searches.

# Configuration

BlueFeather uses `bluefeather.json` for window and backend settings.

Common locations:

- `build-debug/bin/bluefeather.json`
- `build/bin/bluefeather.json`
- `build-debug/bin/BlueFeather-debug.app/Contents/Resources/bluefeather.json`
- `build/bin/BlueFeather.app/Contents/Resources/bluefeather.json`

The default macOS graphics backend is Metal. If you need to change it, edit `bluefeather.json` before launching the app.

# Development

Important source layout:

- `hm64/src` and `hm64/include`: imported HM64 game code
- `hm64/bluefeather/src` and `hm64/bluefeather/include`: BlueFeather port code
- `libultraship`: platform, windowing, rendering, audio, and archive runtime
- `Torch`: archive packaging tool for `.o2r` assets

Useful commands:

```bash
./launch-lldb-debug.sh
cmake --build --preset debug
```

# License

BlueFeather follows the licensing terms of the HM64 decomp project it is built from.

`libultraship` and `Torch` are separate dependencies with their own licenses.

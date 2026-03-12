# BlueFeather

BlueFeather is a native PC port of Harvest Moon 64.

BlueFeather does not include copyrighted game assets. To build and run the port, you need this repository, its submodules, and a matching `hm64-decomp` checkout beside it.

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

### 2. Place `hm64-decomp` next to this repository

BlueFeather expects this layout during configure and build:

```text
../BlueFeather
../hm64-decomp
```

### 3. Install prerequisites

macOS dependencies:

```bash
brew install cmake ninja python sdl2 glew libzip tinyxml2 nlohmann-json
```

### 4. Build BlueFeather

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

### 5. Launch the game

Debug build:

```bash
./build-debug/bin/BlueFeather-debug.app/Contents/MacOS/BlueFeather-debug
```

Release build:

```bash
./build/bin/BlueFeather.app/Contents/MacOS/BlueFeather
```

# Build Output

The build generates and stages these runtime files automatically:

- `hm64.o2r`
- `BlueFeather.o2r`
- `bluefeather.json`

On macOS they are copied both to the build output directory and into the app bundle resources.

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

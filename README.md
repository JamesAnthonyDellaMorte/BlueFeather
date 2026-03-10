# Moonwright

Moonwright is a standalone Harvest Moon 64 port project built on top of [libultraship](https://github.com/Kenix3/libultraship).
The repository layout is intentionally modeled after Shipwright: the port owns a local HM64 game subtree instead of reaching back
into a separate decomp repository at build time.

## Status

🎮 **FUNCTIONAL** - Moonwright compiles and runs with a working window, render loop, and active HM64 runtime integration.

### What's Working
- ✅ Libultraship builds successfully
- ✅ Moonwright executable compiles (macOS ARM64)
- ✅ Asset extraction from original ROM
- ✅ CMake build system configured
- ✅ Window/Graphics initialization
- ✅ Render loop with GUI pipeline
- ✅ Input/controller initialization

### What's Not Working (Yet)
- ❌ Full HM64 game-flow integration
- ❌ Complete N64 display list compatibility
- ❌ Audio
- ❌ Save/load

## Prerequisites

### macOS
- macOS 14.0+ (tested on macOS 26.1)
- Xcode Command Line Tools
- Homebrew packages:
```bash
brew install cmake ninja sdl2 glew libzip tinyxml2 nlohmann-json
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install cmake ninja-build libsdl2-dev libglew-dev libzip-dev \
    libtinyxml2-dev nlohmann-json3-dev
```

### Windows
- Visual Studio 2022
- vcpkg for dependencies

## Setup

### 1. Clone Moonwright with submodules

Moonwright carries `libultraship` as a Git submodule:

```bash
git clone --recurse-submodules git@github.com:JamesAnthonyDellaMorte/Moonwright.git
cd Moonwright
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

## Building

### CMake Builds

Moonwright uses direct CMake builds, following the same repo-owned workflow
Shipwright uses.

From the repo root:

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
build             # Release
build-relwithdeb  # RelWithDebInfo
build-debug       # Debug
```

Executable paths:

```text
build/bin/Moonwright.app/Contents/MacOS/Moonwright
build-relwithdeb/bin/Moonwright.app/Contents/MacOS/Moonwright
build-debug/bin/Moonwright-debug.app/Contents/MacOS/Moonwright-debug
```

## Running

### Run Directly

```bash
cd /Users/jamesdellamorte/Moonwright/build/bin
./Moonwright.app/Contents/MacOS/Moonwright
```

### Expected Output

```
[INFO] Moonwright starting...
[INFO] Added asset source: "/Users/jamesdellamorte/Moonwright/build/bin/Moonwright.app/Contents/Resources/Moonwright.o2r"
[DEBUG] Creating libultraship bootstrap context...
[DEBUG] Creating window and control deck...
[DEBUG] Initializing libultraship context...
[INFO] Libultraship context created successfully
[DEBUG] About to create HM64Game...
[DEBUG] About to call game.Init()...
[INFO] Initializing HM64 Game...
[INFO] HM64 Game initialization complete
[DEBUG] About to call game.Run()...
[INFO] Starting game main loop
```

A window should open and boot the current Moonwright runtime path.

## Project Structure

```
Moonwright/
├── CMakeLists.txt          # Top-level project orchestrator
├── CMakePresets.json       # Configure/build entrypoints
├── README.md
├── hm64.json               # Runtime configuration
├── hm64/                   # Game subtree, analogous to Shipwright's soh/
│   ├── CMakeLists.txt      # Game target wiring
│   ├── assets/             # Imported HM64 assets snapshot used to build Moonwright.o2r
│   ├── include/            # Imported HM64 headers snapshot
│   ├── src/                # Imported HM64 source snapshot
│   ├── tools/              # Imported HM64 tools snapshot
│   └── moonwright/         # Port-specific code and overrides
│       ├── include/
│       └── src/
├── CMake/
│   ├── HideSystemSpdlog.cmake
│   └── Info.plist.in
└── libultraship/
```

`hm64/` is the owned local game subtree. `hm64/src` and `hm64/include` are the
imported HM64 source snapshots. `hm64/moonwright` is the port-specific layer,
filling the same role that Shipwright's `soh/soh` layer fills over `soh/src`.

## Configuration (hm64.json)

```json
{
    "Window": {
        "Width": 640,
        "Height": 480,
        "Fullscreen": false,
        "Resizable": true,
        "Title": "Moonwright"
    },
    "Graphics": {
        "Renderer": "OpenGL",
        "VSync": true,
        "MSAA": 0,
        "InternalResolution": 1.0
    },
    "Audio": {
        "Enabled": true,
        "Volume": 1.0
    },
    "Input": {
        "ControllerEnabled": true,
        "KeyboardEnabled": true
    },
    "Game": {
        "Region": "US",
        "Language": "English"
    }
}
```

## Build Model

### Libultraship Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                        Moonwright                           │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────┐  │
│  │   main.cpp  │→ │  HM64Game   │→ │  Ship::Context      │  │
│  │             │  │             │  │  (libultraship)     │  │
│  └─────────────┘  └─────────────┘  └─────────────────────┘  │
│                                              │              │
│                    ┌─────────────────────────┼──────────┐   │
│                    ↓                         ↓          ↓   │
│              ┌──────────┐              ┌──────────┐ ┌──────┐│
│              │  Window  │              │  Audio   │ │Input ││
│              │ (SDL2)   │              │          │ │      ││
│              └──────────┘              └──────────┘ └──────┘│
│                    │                                         │
│              ┌──────────┐                                    │
│              │ Fast3D   │  ← N64 Display List Interpreter   │
│              │ Renderer │                                    │
│              └──────────┘                                    │
└─────────────────────────────────────────────────────────────┘
```

Moonwright builds from the local `hm64/` snapshot rather than reaching into a
separate decomp checkout. That is the important Shipwright-style design choice:
the port repo owns the exact game sources it builds.

## Troubleshooting

### spdlog/fmt Version Mismatch

If you see errors like:
```
Undefined symbols for architecture arm64:
  "spdlog::details::log_msg::log_msg(spdlog::source_loc, fmt::v12::basic_string_view<char>..."
```

This means the system spdlog was found instead of the fetched one. Make sure to use the toolchain file:
```bash
-DCMAKE_TOOLCHAIN_FILE=/tmp/hide_spdlog.cmake
```

### macOS SDK Not Found

```bash
export CMAKE_OSX_SYSROOT=$(xcrun --show-sdk-path)
```

### Missing Dependencies

macOS:
```bash
brew install cmake sdl2 glew libzip spdlog fmt tinyxml2 nlohmann-json
```

## Next Steps for Development

### 1. Asset Archive

Moonwright now follows the Shipwright-style packaged-archive path:

- build `Moonwright.o2r` from `hm64/assets`
- copy `Moonwright.o2r` beside the executable / into the app bundle
- mount the archive at runtime instead of loose asset directories

### 2. Integrate Game Code

Modify `hm64_game.cpp` to actually call HM64 functions:

```cpp
void HM64Game::Run() {
    // Instead of placeholder loop:
    // Call original mainproc or mainLoop
    
    // Need to bridge:
    // - nuGfx* functions → libultraship graphics
    // - os* functions → libultraship OS abstractions
    // - Audio calls → libultraship audio
}
```

### 3. Graphics Bridge

HM64 uses N64 display lists. libultraship has Fast3D which can interpret them. Need to:
- Set up display list buffer
- Hook up `gSPSegment`, `gSPVertex`, etc.
- Connect to Fast3D renderer

### 4. Controller Input

Set up controller mappings in config or code:
```cpp
auto controlDeck = m_context->GetControlDeck();
// Configure N64 button mappings
```

## Resources

- [libultraship GitHub](https://github.com/Kenix3/libultraship)
- [Ship of Harkinian](https://github.com/HarbourMasters/Shipwright) - Reference implementation
- [Fast3D Documentation](https://github.com/Kenix3/libultraship/tree/main/src/graphic/Fast3D)
- [HM64 Decomp Project](https://github.com/harvestwhisperer/hm64-decomp)

## License

This PC port follows the same license as the original HM64 decomp project.
Libultraship is licensed under MIT.

---

**Note**: This is a work in progress. The build succeeds but the game won't run yet without further integration work.

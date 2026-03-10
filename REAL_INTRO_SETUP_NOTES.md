# Real Intro Setup Worklog

This file explains the work that got the PC port from a custom asset-viewer/title-screen bootstrap to the point where the real opening sequence starts, the first logo renders, and the cherry blossoms show up before the later black-screen handoff.

Code commit for this state:

- `d367ccb` `pc_port: boot opening logos through intro runtime`

## Goal

The target was not "show something on screen." The target was:

1. Stop booting directly into the fake title-only path.
2. Start the real HM64 intro logic far enough to execute the opening cutscene.
3. Render the first logo sequence through the actual game logic instead of a custom UI preview.
4. Keep host-only behavior in the PC-port layer as much as possible, closer to Shipwright's split.

## What Was Wrong At The Start

The port originally had several separate failure modes:

1. Startup booted a custom title runtime, not the real intro path.
2. The cutscene system was using host pointers and N64-style addresses interchangeably.
3. Big-endian N64 data was being decoded through native host loads in multiple places.
4. The ROM loader only knew about a narrow set of hand-picked title assets.
5. The intro runtime was running in a custom frame order, not the game's real per-frame ordering.
6. The renderer was mis-handling some sprite/texture paths, which caused shredded logos, tiny white tiles, and stale sprite frames.

The result was a sequence of crashes and bad renders:

- null dereferences during context/window teardown
- crashes during GUI/console initialization
- Metal/OpenGL frame-end crashes
- broken title logo rendering
- dog animation reusing stale data
- cutscene bytecode reading garbage
- black screens from unmapped ROM reads

## High-Level Strategy

The approach that worked was incremental:

1. Stabilize libultraship startup and the PC build script.
2. Get a clean title-runtime loop alive.
3. Switch from the asset-preview runtime to the real opening-cutscene bootstrap.
4. Fix address translation and endianness so intro data is decoded correctly.
5. Expand ROM access so the intro can actually DMA what it asks for.
6. Fix renderer/runtime ordering issues that made the first logo display incorrectly.

## Major Changes

### 1. Stabilized startup and the PC build path

Files:

- [pc_port/build.sh](/Users/jamesdellamorte/hm64-decomp/pc_port/build.sh)
- [pc_port/src/main.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/main.cpp)
- [pc_port/src/hm64_game.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_game.cpp)
- [pc_port/libultraship/src/ship/Context.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/libultraship/src/ship/Context.cpp)
- [pc_port/libultraship/src/ship/window/Window.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/libultraship/src/ship/window/Window.cpp)

What changed:

- fixed null teardown paths around `SaveWindowToConfig()`
- fixed early bootstrap so window/control-deck/context come up in the right order
- made `build.sh` actually manage configure/build/run/debug sanely
- added debugger support and switched the macOS debug path to LLDB instead of GNU gdb

Why it mattered:

- the port had to stop crashing before any HM64 runtime work was meaningful

### 2. Split the PC port more like Shipwright

Files:

- [pc_port/CMakeLists.txt](/Users/jamesdellamorte/hm64-decomp/pc_port/CMakeLists.txt)
- [pc_port/hm64/CMakeLists.txt](/Users/jamesdellamorte/hm64-decomp/pc_port/hm64/CMakeLists.txt)
- [pc_port/hm64/include/system/entity.h](/Users/jamesdellamorte/hm64-decomp/pc_port/hm64/include/system/entity.h)
- [pc_port/src/game_stubs.c](/Users/jamesdellamorte/hm64-decomp/pc_port/src/game_stubs.c)
- [pc_port/src/sprite_stubs.c](/Users/jamesdellamorte/hm64-decomp/pc_port/src/sprite_stubs.c)

What changed:

- the PC target now builds from a dedicated `pc_port/hm64` subtree
- host-only shims and shadow headers were moved into `pc_port/`
- the executable now links the port-owned runtime sources instead of relying on the old preview-only setup

Why it mattered:

- this made it possible to patch host behavior without constantly mixing everything into the ROM-facing tree

### 3. Replaced the fake title-only bootstrap with an intro-capable runtime

Files:

- [pc_port/src/hm64_title_runtime.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_title_runtime.cpp)
- [pc_port/src/hm64_game.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_game.cpp)
- [src/game/gameStart.c](/Users/jamesdellamorte/hm64-decomp/src/game/gameStart.c)
- [src/mainproc.c](/Users/jamesdellamorte/hm64-decomp/src/mainproc.c)

What changed:

- the runtime now launches the opening cutscene path instead of immediately initializing the title screen
- callback registration was expanded so the intro can run through the game’s main-loop callback system
- `HM64Game` now drives that runtime instead of the preview UI when the intro path initializes cleanly

Why it mattered:

- this is the change that moved the port from "fake title boot" to "real opening sequence starts running"

### 4. Fixed cutscene address translation on the host

Files:

- [pc_port/src/ld_symbols.c](/Users/jamesdellamorte/hm64-decomp/pc_port/src/ld_symbols.c)
- [pc_port/src/hm64_ram.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_ram.cpp)
- [pc_port/include/ld_symbols.h](/Users/jamesdellamorte/hm64-decomp/pc_port/include/ld_symbols.h)

What changed:

- cutscene bytecode buffers were remapped into the host shadow-RAM image at their expected N64-relative locations
- host translation for `0x802F4000` / `0x802F5000` and nearby ranges was cleaned up
- the address-translation path now falls back to shadow RAM for relevant `0x80000000`-range sprite/cutscene buffers

Why it mattered:

- the intro cutscene bytecode and sprite DMA commands were previously reading from the wrong host pointers
- this was one of the main causes of invalid opcode execution and bogus cutscene state

### 5. Fixed endianness and raw-byte decoding for host execution

Files:

- [pc_port/include/common.h](/Users/jamesdellamorte/hm64-decomp/pc_port/include/common.h)
- [src/system/cutscene.c](/Users/jamesdellamorte/hm64-decomp/src/system/cutscene.c)
- [src/system/cutscene.h](/Users/jamesdellamorte/hm64-decomp/src/system/cutscene.h)
- [src/system/globalSprites.c](/Users/jamesdellamorte/hm64-decomp/src/system/globalSprites.c)
- [src/system/globalSprites.h](/Users/jamesdellamorte/hm64-decomp/src/system/globalSprites.h)
- [src/system/sprite.c](/Users/jamesdellamorte/hm64-decomp/src/system/sprite.c)

What changed:

- added byte-wise helpers for big-endian cutscene and sprite data
- replaced fragile typed `u16*` / `u32*` host reads with explicit byte decoding in the intro-critical paths
- fixed bitmap metadata and animation frame metadata stepping so the host path interprets raw sprite data correctly

Why it mattered:

- N64 data is not safe to decode through naive native loads on this host path
- this directly affected the opening logos, title sprites, and cutscene executor behavior

### 6. Expanded ROM access from narrow segment lists to real fallback reads

Files:

- [pc_port/include/hm64_host_rom.h](/Users/jamesdellamorte/hm64-decomp/pc_port/include/hm64_host_rom.h)
- [pc_port/src/hm64_host_rom.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_host_rom.cpp)
- [pc_port/src/rom_symbols.c](/Users/jamesdellamorte/hm64-decomp/pc_port/src/rom_symbols.c)

What changed:

- added the real ROM image as a fallback source instead of zero-filling any unmapped DMA request
- mounted the explicit title and intro segments needed by the early cutscene path
- corrected several symbol/segment definitions used by the intro

Why it mattered:

- once the intro started really running, it immediately requested ROM ranges the old loader did not know about
- before this change, the game stayed alive but rendered nothing because sprite DMA kept reading zeros

### 7. Fixed renderer issues that affected the first visible intro/logo output

Files:

- [pc_port/libultraship/src/fast/interpreter.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/libultraship/src/fast/interpreter.cpp)
- [pc_port/src/nugfx.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/nugfx.cpp)
- [pc_port/hm64/src/system/sprite.c](/Users/jamesdellamorte/hm64-decomp/pc_port/hm64/src/system/sprite.c)
- [pc_port/hm64/src/system/graphic.c](/Users/jamesdellamorte/hm64-decomp/pc_port/hm64/src/system/graphic.c)

What changed:

- fixed texture upload width/stride handling in the interpreter so CI textures stop rendering with diagonal shredding
- added cache invalidation on DMA updates so animated sprite data is not stuck on stale texture contents
- treated bitmap scene-node `z` scale of `0` as `1` on the host path so flat HM64 sprites do not degenerate
- kept the PC sprite/bitmap path aligned with what the intro expects

Why it mattered:

- this was the difference between “it boots” and “the first logo actually renders recognizably”

### 8. Fixed the runtime frame ordering for the intro

Files:

- [src/mainLoop.c](/Users/jamesdellamorte/hm64-decomp/src/mainLoop.c)
- [pc_port/hm64/src/mainLoop.c](/Users/jamesdellamorte/hm64-decomp/pc_port/hm64/src/mainLoop.c)
- [pc_port/src/hm64_title_runtime.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_title_runtime.cpp)

What changed:

- the port runtime was not following the same per-frame order as the game’s `mainLoop`
- the current fix moved the active title/intro runtime closer to the real order by clearing bitmap/scene state before executing cutscene commands, then running sprite update/DMA/bitmap update/draw

Why it mattered:

- the first logo sequence visibly improved after this, and it was the last change before the cherry blossoms showed up correctly

## Debugging Notes

Important debugger lesson:

- do not use LLDB `p` / the expression evaluator on this setup unless necessary
- use `frame variable`, `target variable`, and `memory read` instead

Why:

- the expression evaluator caused at least one debugger/session failure while chasing the intro path

Useful runtime signals during this work:

- `[HM64_ROM] Unmapped ROM read ...`
- `[CUTSCENE] ...`
- `[SPAWN] ...`
- `[SPRITE] updateBitmaps ...`
- `[HM64_GFX] drawFrame called ...`

Those logs made it possible to tell the difference between:

- a dead cutscene path
- a live cutscene with bad ROM data
- a live cutscene with bad sprite decoding
- a renderer-order problem

## What Works In This Commit

At this point the port can:

1. boot through the intro runtime instead of straight to the preview UI
2. execute the opening cutscene path
3. render the first visible intro/logo sequence instead of staying black
4. reach the cherry blossom part of the intro

The user-confirmed visible result for this commit was:

- the first visible logo sequence improved
- the cherry blossoms loaded correctly
- the runtime then progressed to a later black-screen problem

That is real forward progress. The intro is no longer blocked at the first logo.

## What Is Still Not Done

This commit does not finish the whole opening sequence.

Known remaining issues after this point:

1. later handoff still goes to a black screen
2. title-screen dog animation still needs proper behavior
3. the whole intro-to-title transition is not fully correct yet
4. some host fixes still live in shared `src/` files and are not fully isolated

## Most Important Files For The Next Pass

If work resumes from here, start with these:

- [pc_port/src/hm64_title_runtime.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_title_runtime.cpp)
- [pc_port/src/hm64_host_rom.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/src/hm64_host_rom.cpp)
- [pc_port/src/ld_symbols.c](/Users/jamesdellamorte/hm64-decomp/pc_port/src/ld_symbols.c)
- [src/system/cutscene.c](/Users/jamesdellamorte/hm64-decomp/src/system/cutscene.c)
- [src/system/globalSprites.c](/Users/jamesdellamorte/hm64-decomp/src/system/globalSprites.c)
- [pc_port/libultraship/src/fast/interpreter.cpp](/Users/jamesdellamorte/hm64-decomp/pc_port/libultraship/src/fast/interpreter.cpp)

## Verification Style Used

During iteration, the safe verification step was:

```sh
cmake --build pc_port/build --target HM64 --parallel 4
```

The user then ran:

```sh
cd pc_port
./build.sh run
```

That separation was intentional. The user wanted to drive runtime checks locally while the code-side iteration and build verification happened here.

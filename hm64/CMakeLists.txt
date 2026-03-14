set(GAME_NAME "BlueFeather")
set(GAME_SHORT_NAME "BlueFeather")
set(HM64_BASE_ASSET_ARCHIVE "hm64.o2r")
set(BLUEFEATHER_PORT_ASSET_ARCHIVE "${GAME_SHORT_NAME}.o2r")

set(HM64_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BLUEFEATHER_ROOT ${HM64_ROOT}/bluefeather)
set(BLUEFEATHER_PROJECT_ROOT ${HM64_ROOT}/..)
set(HM64_CONFIG_ROOT ${HM64_ROOT}/config/us)
set(HM64_SPLAT_CONFIG ${HM64_CONFIG_ROOT}/splat.us.yaml)
set(HM64_RAM_SYMBOLS_FILE ${HM64_CONFIG_ROOT}/symbol_addrs.txt)
set(HM64_TORCH_CONFIG ${BLUEFEATHER_PROJECT_ROOT}/config.yml)
set(HM64_TORCH_YAML_ROOT ${HM64_ROOT}/assets/yaml)
set(BLUEFEATHER_DEFAULT_CONFIG ${BLUEFEATHER_PROJECT_ROOT}/bluefeather.default.json)
set(HM64_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(HM64_RUNTIME_ARCHIVE_TABLE "${HM64_GENERATED_DIR}/runtime_archive_rom_table.h")
option(BLUEFEATHER_BUILD_RUNTIME_ASSETS "Generate runtime O2R archives during the build" ON)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
include(ExternalProject)

set(TORCH_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/Torch
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DUSE_STANDALONE=ON
    -DBUILD_STORMLIB=OFF
    -DBUILD_SM64=OFF
    -DBUILD_MK64=OFF
    -DBUILD_SF64=OFF
    -DBUILD_FZERO=OFF
    -DBUILD_MARIO_ARTIST=OFF
    -DBUILD_NAUDIO=ON
)

if(APPLE AND CMAKE_OSX_DEPLOYMENT_TARGET)
    list(APPEND TORCH_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
endif()

ExternalProject_Add(TorchExternal
    PREFIX TorchExternal
    SOURCE_DIR ${BLUEFEATHER_PROJECT_ROOT}/Torch
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/TorchExternal/src/TorchExternal-build/torch
    CMAKE_ARGS ${TORCH_CMAKE_ARGS}
)

ExternalProject_Get_Property(TorchExternal install_dir)
if(MSVC)
    set(TORCH_EXECUTABLE ${install_dir}/src/TorchExternal-build/$<CONFIGURATION>/torch)
else()
    set(TORCH_EXECUTABLE ${install_dir}/src/TorchExternal-build/torch)
endif()

set(HM64_PORT_SOURCES
    ${BLUEFEATHER_ROOT}/src/main.cpp
    ${BLUEFEATHER_ROOT}/src/hm64_game.cpp
    ${BLUEFEATHER_ROOT}/src/hm64_gu_compat.c
    ${BLUEFEATHER_ROOT}/src/hm64_ram.cpp
    ${BLUEFEATHER_ROOT}/src/libmus.cpp
    ${BLUEFEATHER_ROOT}/src/nugfx.cpp
    ${BLUEFEATHER_ROOT}/src/ui/BlueFeatherUI.cpp
    ${BLUEFEATHER_ROOT}/src/ultra64_compat.cpp
    ${BLUEFEATHER_ROOT}/src/libmus/player.c
)

set(HM64_RUNTIME_SOURCES
    ${HM64_ROOT}/src/mainproc.c
    ${BLUEFEATHER_ROOT}/src/mainLoop.c
    ${HM64_ROOT}/src/buffers/characterAvatarsSpriteBuffer.c
    ${HM64_ROOT}/src/buffers/cutsceneBytecodeBuffer.c
    ${HM64_ROOT}/src/buffers/dialogueBytecodeBuffer.c
    ${HM64_ROOT}/src/buffers/dialogueIconSpriteBuffer.c
    ${HM64_ROOT}/src/buffers/sramBuffer.c
    ${HM64_ROOT}/src/buffers/farmRankingsBuffer.c
    ${HM64_ROOT}/src/buffers/textBuffer.c
    ${HM64_ROOT}/src/buffers/fontBuffer.c
    ${HM64_ROOT}/src/buffers/frameBuffer.c
    ${HM64_ROOT}/src/buffers/mapDataBuffer.c
    ${HM64_ROOT}/src/buffers/mapObjectBuffer.c
    ${HM64_ROOT}/src/buffers/messageBoxBuffer.c
    ${HM64_ROOT}/src/buffers/messageBoxesBuffer.c
    ${HM64_ROOT}/src/buffers/namingScreenBuffer.c
    ${HM64_ROOT}/src/buffers/playerSpriteBuffer.c
    ${HM64_ROOT}/src/buffers/shadowSpriteBuffer.c
    ${HM64_ROOT}/src/buffers/spriteBuffer.c
    ${HM64_ROOT}/src/buffers/unknownBuffer.c
    ${HM64_ROOT}/src/data/audio/sfx.c
    ${HM64_ROOT}/src/data/fieldTileMaps/cutsceneFieldTiles.c
    ${HM64_ROOT}/src/data/fieldTileMaps/fieldTiles.c
    ${HM64_ROOT}/src/game/gameAudio.c
    ${HM64_ROOT}/src/game/game.c
    ${HM64_ROOT}/src/game/gameFile.c
    ${HM64_ROOT}/src/game/initialize.c
    ${HM64_ROOT}/src/game/gameStart.c
    ${HM64_ROOT}/src/game/level.c
    ${HM64_ROOT}/src/game/namingScreen.c
    ${HM64_ROOT}/src/game/npc.c
    ${HM64_ROOT}/src/game/overlayScreens.c
    ${HM64_ROOT}/src/game/player.c
    ${HM64_ROOT}/src/game/shop.c
    ${HM64_ROOT}/src/game/transition.c
    ${HM64_ROOT}/src/game/title.c
    ${HM64_ROOT}/src/game/tv.c
    ${HM64_ROOT}/src/game/cutscenes.c
    ${HM64_ROOT}/src/game/animals.c
    ${HM64_ROOT}/src/game/evaluation.c
    ${HM64_ROOT}/src/game/fieldObjects.c
    ${HM64_ROOT}/src/game/gameStatus.c
    ${HM64_ROOT}/src/game/items.c
    ${HM64_ROOT}/src/game/levelInteractions.c
    ${HM64_ROOT}/src/game/load.c
    ${HM64_ROOT}/src/game/time.c
    ${HM64_ROOT}/src/game/weather.c
    ${HM64_ROOT}/src/system/audio.c
    ${HM64_ROOT}/src/system/controller.c
    ${HM64_ROOT}/src/system/cutscene.c
    ${HM64_ROOT}/src/system/dialogue.c
    ${HM64_ROOT}/src/system/entity.c
    ${HM64_ROOT}/src/system/flags.c
    ${BLUEFEATHER_ROOT}/src/system/globalSprites.c
    ${BLUEFEATHER_ROOT}/src/system/graphic.c
    ${HM64_ROOT}/src/system/interpolation.c
    ${HM64_ROOT}/src/system/map.c
    ${HM64_ROOT}/src/system/mapController.c
    ${HM64_ROOT}/src/system/math.c
    ${HM64_ROOT}/src/system/memory.c
    ${HM64_ROOT}/src/system/message.c
    ${HM64_ROOT}/src/system/numberSprites.c
    ${HM64_ROOT}/src/system/sceneGraph.c
    ${BLUEFEATHER_ROOT}/src/system/sprite.c
    ${HM64_ROOT}/src/system/spriteDMAManager.c
    ${HM64_ROOT}/src/system/staticGfx.c
    ${HM64_ROOT}/src/data/animationScripts/animationScripts.c
)

set(HM64_COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_BINARY_DIR}
    ${BLUEFEATHER_ROOT}/src
    ${BLUEFEATHER_ROOT}/include
    ${BLUEFEATHER_ROOT}/src/libmus
    ${HM64_ROOT}/include
    ${HM64_ROOT}/src
    ${LIBULTRASHIP_DIR}/include
    ${LIBULTRASHIP_DIR}/include/libultraship
)

set(HM64_ROM_SYMBOL_ASM "${CMAKE_CURRENT_BINARY_DIR}/generated/rom_symbols.c")
set(HM64_ROM_SYMBOL_HEADER "${CMAKE_CURRENT_BINARY_DIR}/generated/rom_symbol_overrides.h")
file(GLOB_RECURSE HM64_RUNTIME_METADATA_INPUTS CONFIGURE_DEPENDS
    "${HM64_CONFIG_ROOT}/*"
    "${HM64_ROOT}/tools/libhm64/*"
)
add_custom_command(
    OUTPUT ${HM64_RUNTIME_ARCHIVE_TABLE}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${HM64_GENERATED_DIR}
    COMMAND ${Python3_EXECUTABLE}
        ${HM64_ROOT}/tools/generate_torch_runtime_metadata.py
        --table-header ${HM64_RUNTIME_ARCHIVE_TABLE}
    DEPENDS
        ${HM64_ROOT}/tools/generate_torch_runtime_metadata.py
        ${HM64_RUNTIME_METADATA_INPUTS}
    COMMENT "Generating BlueFeather runtime archive table"
    VERBATIM
)
add_custom_target(GenerateRuntimeArchiveTable DEPENDS ${HM64_RUNTIME_ARCHIVE_TABLE})

if(MSVC)
    set(HM64_ROM_SYMBOL_OUTPUT ${HM64_ROM_SYMBOL_HEADER})
else()
    set(HM64_ROM_SYMBOL_OUTPUT ${HM64_ROM_SYMBOL_ASM})
endif()

add_custom_command(
    OUTPUT ${HM64_ROM_SYMBOL_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${HM64_GENERATED_DIR}
    COMMAND ${Python3_EXECUTABLE}
        ${HM64_ROOT}/tools/generate_rom_symbol_asm.py
        --ld-header ${HM64_ROOT}/include/ld_symbols.h
        --splat-config ${HM64_SPLAT_CONFIG}
        --output ${HM64_ROM_SYMBOL_OUTPUT}
    DEPENDS
        ${HM64_ROOT}/tools/generate_rom_symbol_asm.py
        ${HM64_ROOT}/include/ld_symbols.h
        ${HM64_SPLAT_CONFIG}
    COMMENT "Generating BlueFeather ROM symbols"
    VERBATIM
)

add_custom_target(GenerateRomSymbols DEPENDS ${HM64_ROM_SYMBOL_OUTPUT})

if(NOT MSVC)
    list(APPEND HM64_PORT_SOURCES ${HM64_ROM_SYMBOL_ASM})
endif()

add_executable(${GAME_SHORT_NAME} ${HM64_PORT_SOURCES} ${HM64_RUNTIME_SOURCES})
add_dependencies(${GAME_SHORT_NAME} GenerateRuntimeArchiveTable GenerateRomSymbols)

if(MSVC)
    set(HM64_PLAYER_FORCED_INCLUDE "/FImath.h")
else()
    set(HM64_PLAYER_FORCED_INCLUDE "-include;math.h")
endif()

set_source_files_properties(${BLUEFEATHER_ROOT}/src/libmus/player.c PROPERTIES
    COMPILE_DEFINITIONS "NU_SYSTEM;_AUDIOVISIBLE"
    COMPILE_OPTIONS "${HM64_PLAYER_FORCED_INCLUDE}"
)

target_include_directories(${GAME_SHORT_NAME} PRIVATE ${HM64_COMMON_INCLUDE_DIRS})

target_link_libraries(${GAME_SHORT_NAME}
    PRIVATE
        libultraship
)

target_compile_definitions(${GAME_SHORT_NAME}
    PRIVATE
        HM64_PC_PORT
        F3DEX_GBI_2
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(${GAME_SHORT_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
            -Wno-unused-variable
            -Wno-int-conversion
            -Wno-incompatible-pointer-types
            -Wno-pointer-to-int-cast
    )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # The generated ROM segment symbols are still consumed with N64-style
    # address semantics, so the executable must link as a normal ELF binary.
    target_compile_options(${GAME_SHORT_NAME} PRIVATE -fno-pie)
    target_link_options(${GAME_SHORT_NAME} PRIVATE -no-pie)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set_target_properties(${GAME_SHORT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${BLUEFEATHER_PROJECT_ROOT}/CMake/Info.plist.in
        MACOSX_BUNDLE_BUNDLE_NAME "BlueFeather"
        MACOSX_BUNDLE_BUNDLE_IDENTIFIER "com.hm64.bluefeather"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_LONG_VERSION_STRING "1.0.0"
    )
endif()

set_target_properties(${GAME_SHORT_NAME} PROPERTIES
    OUTPUT_NAME_DEBUG "${GAME_SHORT_NAME}-debug"
)

if(BLUEFEATHER_BUILD_RUNTIME_ASSETS)
    file(GLOB_RECURSE HM64_TORCH_YAML_FILES CONFIGURE_DEPENDS
        "${HM64_TORCH_YAML_ROOT}/*"
    )
    file(GLOB_RECURSE BLUEFEATHER_PORT_ASSET_FILES CONFIGURE_DEPENDS
        "${BLUEFEATHER_PROJECT_ROOT}/port/*"
    )

    set(HM64_SOURCE_O2R_FILE "${BLUEFEATHER_PROJECT_ROOT}/${HM64_BASE_ASSET_ARCHIVE}")
    set(HM64_BASE_O2R_FILE "${CMAKE_CURRENT_BINARY_DIR}/${HM64_BASE_ASSET_ARCHIVE}")
    add_custom_command(
        OUTPUT ${HM64_BASE_O2R_FILE}
        COMMAND ${CMAKE_COMMAND} -E rm -f ${HM64_SOURCE_O2R_FILE} ${HM64_BASE_O2R_FILE}
        COMMAND ${TORCH_EXECUTABLE}
            o2r
            baserom.us.z64
            -s ${BLUEFEATHER_PROJECT_ROOT}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${HM64_SOURCE_O2R_FILE}
            ${HM64_BASE_O2R_FILE}
        DEPENDS
            ${BLUEFEATHER_PROJECT_ROOT}/baserom.us.z64
            ${HM64_TORCH_CONFIG}
            ${HM64_TORCH_YAML_FILES}
            TorchExternal
        WORKING_DIRECTORY ${BLUEFEATHER_PROJECT_ROOT}
        COMMENT "Generating ${HM64_BASE_ASSET_ARCHIVE}"
        VERBATIM
    )
    add_custom_target(GenerateHm64Otr DEPENDS ${HM64_BASE_O2R_FILE})
    add_dependencies(GenerateHm64Otr TorchExternal)

    set(BLUEFEATHER_SOURCE_PORT_O2R_FILE "${BLUEFEATHER_PROJECT_ROOT}/${BLUEFEATHER_PORT_ASSET_ARCHIVE}")
    set(BLUEFEATHER_PORT_O2R_FILE "${CMAKE_CURRENT_BINARY_DIR}/${BLUEFEATHER_PORT_ASSET_ARCHIVE}")
    add_custom_command(
        OUTPUT ${BLUEFEATHER_PORT_O2R_FILE}
        COMMAND ${CMAKE_COMMAND} -E rm -f ${BLUEFEATHER_SOURCE_PORT_O2R_FILE} ${BLUEFEATHER_PORT_O2R_FILE}
        COMMAND ${TORCH_EXECUTABLE}
            pack
            port
            ${BLUEFEATHER_PORT_ASSET_ARCHIVE}
            o2r
            --version 1.0.0
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BLUEFEATHER_SOURCE_PORT_O2R_FILE}
            ${BLUEFEATHER_PORT_O2R_FILE}
        DEPENDS
            ${BLUEFEATHER_PORT_ASSET_FILES}
            TorchExternal
        WORKING_DIRECTORY ${BLUEFEATHER_PROJECT_ROOT}
        COMMENT "Generating ${BLUEFEATHER_PORT_ASSET_ARCHIVE}"
        VERBATIM
    )
    add_custom_target(GenerateBlueFeatherOtr DEPENDS ${BLUEFEATHER_PORT_O2R_FILE})
    add_dependencies(GenerateBlueFeatherOtr TorchExternal)

    add_custom_target(ExtractAssets DEPENDS ${HM64_BASE_O2R_FILE} ${BLUEFEATHER_PORT_O2R_FILE})
    add_dependencies(ExtractAssets GenerateHm64Otr)
    add_dependencies(ExtractAssets GenerateBlueFeatherOtr)

    set(HM64_RUNTIME_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_o2r.stamp")
    add_custom_command(
        OUTPUT ${HM64_RUNTIME_ASSET_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${HM64_BASE_O2R_FILE}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${HM64_BASE_ASSET_ARCHIVE}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BLUEFEATHER_PORT_O2R_FILE}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${BLUEFEATHER_PORT_ASSET_ARCHIVE}
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_ASSET_STAMP}
        DEPENDS ${HM64_BASE_O2R_FILE} ${BLUEFEATHER_PORT_O2R_FILE}
        COMMENT "Copying O2R archives to build output"
        VERBATIM
    )
    add_custom_target(copy_assets DEPENDS ${HM64_RUNTIME_ASSET_STAMP})
    add_dependencies(ExtractAssets copy_assets)
endif()

set(GAMECONTROLLERDB_FILE "${CMAKE_CURRENT_BINARY_DIR}/gamecontrollerdb.txt")
if(NOT EXISTS "${GAMECONTROLLERDB_FILE}")
    file(
        DOWNLOAD
        "https://raw.githubusercontent.com/mdqinc/SDL_GameControllerDB/master/gamecontrollerdb.txt"
        "${GAMECONTROLLERDB_FILE}"
        STATUS GAMECONTROLLERDB_DOWNLOAD_STATUS
        TLS_VERIFY ON
    )
    list(GET GAMECONTROLLERDB_DOWNLOAD_STATUS 0 GAMECONTROLLERDB_STATUS_CODE)
    if(NOT GAMECONTROLLERDB_STATUS_CODE EQUAL 0)
        file(REMOVE "${GAMECONTROLLERDB_FILE}")
        message(WARNING "Failed to download gamecontrollerdb.txt (${GAMECONTROLLERDB_DOWNLOAD_STATUS})")
    endif()
endif()

set(HM64_RUNTIME_CONFIG_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_config.stamp")
add_custom_command(
    OUTPUT ${HM64_RUNTIME_CONFIG_STAMP}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BLUEFEATHER_DEFAULT_CONFIG}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bluefeather.json
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_CONFIG_STAMP}
    DEPENDS ${BLUEFEATHER_DEFAULT_CONFIG}
    COMMENT "Copying config file"
    VERBATIM
)
add_custom_target(copy_config DEPENDS ${HM64_RUNTIME_CONFIG_STAMP})
add_dependencies(${GAME_SHORT_NAME} copy_config)

if(EXISTS "${GAMECONTROLLERDB_FILE}")
    set(HM64_RUNTIME_CONTROLLERDB_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_controllerdb.stamp")
    add_custom_command(
        OUTPUT ${HM64_RUNTIME_CONTROLLERDB_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${GAMECONTROLLERDB_FILE}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gamecontrollerdb.txt
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_CONTROLLERDB_STAMP}
        DEPENDS ${GAMECONTROLLERDB_FILE}
        COMMENT "Copying gamecontrollerdb.txt"
        VERBATIM
    )
    add_custom_target(copy_controllerdb DEPENDS ${HM64_RUNTIME_CONTROLLERDB_STAMP})
    add_dependencies(${GAME_SHORT_NAME} copy_controllerdb)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(APP_RESOURCES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<TARGET_BUNDLE_DIR_NAME:${GAME_SHORT_NAME}>/Contents/Resources)

    if(BLUEFEATHER_BUILD_RUNTIME_ASSETS)
        set(HM64_BUNDLE_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_o2r_to_bundle.stamp")
        add_custom_command(
            OUTPUT ${HM64_BUNDLE_ASSET_STAMP}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${HM64_BASE_O2R_FILE}
                ${APP_RESOURCES}/${HM64_BASE_ASSET_ARCHIVE}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${BLUEFEATHER_PORT_O2R_FILE}
                ${APP_RESOURCES}/${BLUEFEATHER_PORT_ASSET_ARCHIVE}
            COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_ASSET_STAMP}
            DEPENDS ${HM64_BASE_O2R_FILE} ${BLUEFEATHER_PORT_O2R_FILE}
            COMMENT "Copying O2R archives to app bundle"
            VERBATIM
        )
        add_custom_target(copy_assets_to_bundle DEPENDS ${HM64_BUNDLE_ASSET_STAMP})
        add_dependencies(ExtractAssets copy_assets_to_bundle)
    endif()

    set(HM64_BUNDLE_CONFIG_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_config_to_bundle.stamp")
    add_custom_command(
        OUTPUT ${HM64_BUNDLE_CONFIG_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BLUEFEATHER_DEFAULT_CONFIG}
            ${APP_RESOURCES}/bluefeather.json
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_CONFIG_STAMP}
        DEPENDS ${BLUEFEATHER_DEFAULT_CONFIG}
        COMMENT "Copying config to app bundle"
        VERBATIM
    )
    add_custom_target(copy_config_to_bundle DEPENDS ${HM64_BUNDLE_CONFIG_STAMP})
    add_dependencies(${GAME_SHORT_NAME} copy_config_to_bundle)

    if(EXISTS "${GAMECONTROLLERDB_FILE}")
        set(HM64_BUNDLE_CONTROLLERDB_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_controllerdb_to_bundle.stamp")
        add_custom_command(
            OUTPUT ${HM64_BUNDLE_CONTROLLERDB_STAMP}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${GAMECONTROLLERDB_FILE}
                ${APP_RESOURCES}/gamecontrollerdb.txt
            COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_CONTROLLERDB_STAMP}
            DEPENDS ${GAMECONTROLLERDB_FILE}
            COMMENT "Copying gamecontrollerdb.txt to app bundle"
            VERBATIM
        )
        add_custom_target(copy_controllerdb_to_bundle DEPENDS ${HM64_BUNDLE_CONTROLLERDB_STAMP})
        add_dependencies(${GAME_SHORT_NAME} copy_controllerdb_to_bundle)
    endif()
endif()

install(TARGETS ${GAME_SHORT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

if(BLUEFEATHER_BUILD_RUNTIME_ASSETS)
    install(FILES ${HM64_BASE_O2R_FILE}
        DESTINATION share/${GAME_SHORT_NAME}
    )

    install(FILES ${BLUEFEATHER_PORT_O2R_FILE}
        DESTINATION share/${GAME_SHORT_NAME}
    )
endif()

install(FILES ${BLUEFEATHER_DEFAULT_CONFIG}
    RENAME bluefeather.json
    DESTINATION share/${GAME_SHORT_NAME}
)

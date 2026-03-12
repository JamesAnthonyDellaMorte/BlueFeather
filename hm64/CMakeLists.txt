set(GAME_NAME "BlueFeather")
set(GAME_SHORT_NAME "BlueFeather")
set(HM64_BASE_ASSET_ARCHIVE "hm64.o2r")
set(BLUEFEATHER_PORT_ASSET_ARCHIVE "${GAME_SHORT_NAME}.o2r")

set(HM64_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BLUEFEATHER_ROOT ${HM64_ROOT}/bluefeather)
set(BLUEFEATHER_PROJECT_ROOT ${HM64_ROOT}/..)
set(HM64_DECOMP_ROOT ${BLUEFEATHER_PROJECT_ROOT}/../hm64-decomp)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(HM64_PORT_SOURCES
    ${BLUEFEATHER_ROOT}/src/main.cpp
    ${BLUEFEATHER_ROOT}/src/hm64_game.cpp
    ${BLUEFEATHER_ROOT}/src/hm64_gu_compat.c
    ${BLUEFEATHER_ROOT}/src/hm64_ram.cpp
    ${BLUEFEATHER_ROOT}/src/hm64_title_globals.c
    ${BLUEFEATHER_ROOT}/src/nugfx.cpp
    ${BLUEFEATHER_ROOT}/src/ultra64_compat.cpp
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
    ${HM64_ROOT}/include
    ${HM64_ROOT}/src
    ${LIBULTRASHIP_DIR}/include
    ${LIBULTRASHIP_DIR}/include/libultraship
)

set(HM64_ROM_SYMBOL_ASM "${CMAKE_CURRENT_BINARY_DIR}/generated/rom_symbols.c")
add_custom_command(
    OUTPUT ${HM64_ROM_SYMBOL_ASM}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/generated
    COMMAND ${Python3_EXECUTABLE}
        ${HM64_ROOT}/tools/generate_rom_symbol_asm.py
        --ld-header ${HM64_ROOT}/include/ld_symbols.h
        --splat-config ${HM64_DECOMP_ROOT}/config/us/splat.us.yaml
        --output ${HM64_ROM_SYMBOL_ASM}
    DEPENDS
        ${HM64_ROOT}/tools/generate_rom_symbol_asm.py
        ${HM64_ROOT}/include/ld_symbols.h
        ${HM64_DECOMP_ROOT}/config/us/splat.us.yaml
    COMMENT "Generating BlueFeather ROM symbols"
    VERBATIM
)

list(APPEND HM64_PORT_SOURCES ${HM64_ROM_SYMBOL_ASM})

add_executable(${GAME_SHORT_NAME} ${HM64_PORT_SOURCES} ${HM64_RUNTIME_SOURCES})

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

file(GLOB_RECURSE HM64_ASSET_FILES CONFIGURE_DEPENDS
    "${HM64_ROOT}/assets/*"
)
list(FILTER HM64_ASSET_FILES EXCLUDE REGEX "/assets/custom(/|$)")
file(GLOB_RECURSE HM64_SHADER_FILES CONFIGURE_DEPENDS
    "${LIBULTRASHIP_DIR}/src/fast/shaders/*"
)
file(GLOB_RECURSE HM64_TOOL_FILES CONFIGURE_DEPENDS
    "${HM64_ROOT}/tools/libhm64/*"
)
file(GLOB HM64_DECOMP_AUDIO_FILES CONFIGURE_DEPENDS
    "${HM64_DECOMP_ROOT}/bin/audio/waveTable*.bin"
)

set(HM64_BASE_CUSTOM_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/custom_base_assets")
set(HM64_RUNTIME_ARCHIVE_TABLE "${CMAKE_CURRENT_BINARY_DIR}/generated/runtime_archive_rom_table.h")
set(HM64_BASE_CUSTOM_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/stage_base_custom_assets.stamp")
add_custom_command(
    OUTPUT ${HM64_BASE_CUSTOM_ASSET_STAMP} ${HM64_RUNTIME_ARCHIVE_TABLE}
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${HM64_BASE_CUSTOM_ASSET_DIR}
    COMMAND ${Python3_EXECUTABLE}
        ${HM64_ROOT}/tools/build_custom_assets.py
        --output-dir ${HM64_BASE_CUSTOM_ASSET_DIR}
        --table-header ${HM64_RUNTIME_ARCHIVE_TABLE}
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BASE_CUSTOM_ASSET_STAMP}
    DEPENDS
        ${HM64_ROOT}/tools/build_custom_assets.py
        ${HM64_ASSET_FILES}
        ${HM64_SHADER_FILES}
        ${HM64_TOOL_FILES}
        ${HM64_DECOMP_AUDIO_FILES}
        ${HM64_ROOT}/include/ld_symbols.h
        ${HM64_DECOMP_ROOT}/config/us/splat.us.yaml
    COMMENT "Staging archive-backed HM64 runtime assets"
    VERBATIM
)
add_custom_target(StageHm64BaseAssets DEPENDS ${HM64_BASE_CUSTOM_ASSET_STAMP} ${HM64_RUNTIME_ARCHIVE_TABLE})

set(BLUEFEATHER_PORT_CUSTOM_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/custom_port_assets")
set(BLUEFEATHER_PORT_CUSTOM_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/stage_port_custom_assets.stamp")
add_custom_command(
    OUTPUT ${BLUEFEATHER_PORT_CUSTOM_ASSET_STAMP}
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${BLUEFEATHER_PORT_CUSTOM_ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BLUEFEATHER_PORT_CUSTOM_ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${LIBULTRASHIP_DIR}/src/fast/shaders
        ${BLUEFEATHER_PORT_CUSTOM_ASSET_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E touch ${BLUEFEATHER_PORT_CUSTOM_ASSET_STAMP}
    DEPENDS ${HM64_SHADER_FILES}
    COMMENT "Staging BlueFeather port assets"
    VERBATIM
)
add_custom_target(StageBlueFeatherPortAssets DEPENDS ${BLUEFEATHER_PORT_CUSTOM_ASSET_STAMP})

set(HM64_BASE_O2R_FILE "${CMAKE_CURRENT_BINARY_DIR}/${HM64_BASE_ASSET_ARCHIVE}")
add_custom_command(
    OUTPUT ${HM64_BASE_O2R_FILE}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${HM64_BASE_O2R_FILE}
    COMMAND ${Python3_EXECUTABLE}
        ${BLUEFEATHER_PROJECT_ROOT}/OTRExporter/extract_assets.py
        -z "$<TARGET_FILE:ZAPD>"
        --norom
        --custom-otr-file ${HM64_BASE_O2R_FILE}
        --custom-assets-path ${HM64_BASE_CUSTOM_ASSET_DIR}
    DEPENDS
        ${BLUEFEATHER_PROJECT_ROOT}/OTRExporter/extract_assets.py
        ${HM64_BASE_CUSTOM_ASSET_STAMP}
        ZAPD
    WORKING_DIRECTORY ${HM64_ROOT}
    COMMENT "Generating ${HM64_BASE_ASSET_ARCHIVE}"
    VERBATIM
)
add_custom_target(GenerateHm64Otr DEPENDS ${HM64_BASE_O2R_FILE})
add_dependencies(GenerateHm64Otr StageHm64BaseAssets)

set(BLUEFEATHER_PORT_O2R_FILE "${CMAKE_CURRENT_BINARY_DIR}/${BLUEFEATHER_PORT_ASSET_ARCHIVE}")
add_custom_command(
    OUTPUT ${BLUEFEATHER_PORT_O2R_FILE}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${BLUEFEATHER_PORT_O2R_FILE}
    COMMAND ${Python3_EXECUTABLE}
        ${BLUEFEATHER_PROJECT_ROOT}/OTRExporter/extract_assets.py
        -z "$<TARGET_FILE:ZAPD>"
        --norom
        --custom-otr-file ${BLUEFEATHER_PORT_O2R_FILE}
        --custom-assets-path ${BLUEFEATHER_PORT_CUSTOM_ASSET_DIR}
    DEPENDS
        ${BLUEFEATHER_PROJECT_ROOT}/OTRExporter/extract_assets.py
        ${BLUEFEATHER_PORT_CUSTOM_ASSET_STAMP}
        ZAPD
    WORKING_DIRECTORY ${HM64_ROOT}
    COMMENT "Generating ${BLUEFEATHER_PORT_ASSET_ARCHIVE}"
    VERBATIM
)
add_custom_target(GenerateBlueFeatherOtr DEPENDS ${BLUEFEATHER_PORT_O2R_FILE})
add_dependencies(GenerateBlueFeatherOtr StageBlueFeatherPortAssets)

add_dependencies(${GAME_SHORT_NAME} GenerateHm64Otr)
add_dependencies(${GAME_SHORT_NAME} GenerateBlueFeatherOtr)

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
add_dependencies(${GAME_SHORT_NAME} copy_assets)

set(HM64_RUNTIME_CONFIG_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_config.stamp")
add_custom_command(
    OUTPUT ${HM64_RUNTIME_CONFIG_STAMP}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BLUEFEATHER_PROJECT_ROOT}/bluefeather.json
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bluefeather.json
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_CONFIG_STAMP}
    DEPENDS ${BLUEFEATHER_PROJECT_ROOT}/bluefeather.json
    COMMENT "Copying config file"
    VERBATIM
)
add_custom_target(copy_config DEPENDS ${HM64_RUNTIME_CONFIG_STAMP})
add_dependencies(${GAME_SHORT_NAME} copy_config)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(APP_RESOURCES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<TARGET_BUNDLE_DIR_NAME:${GAME_SHORT_NAME}>/Contents/Resources)

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
    add_dependencies(${GAME_SHORT_NAME} copy_assets_to_bundle)

    set(HM64_BUNDLE_CONFIG_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_config_to_bundle.stamp")
    add_custom_command(
        OUTPUT ${HM64_BUNDLE_CONFIG_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BLUEFEATHER_PROJECT_ROOT}/bluefeather.json
            ${APP_RESOURCES}/bluefeather.json
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_CONFIG_STAMP}
        DEPENDS ${BLUEFEATHER_PROJECT_ROOT}/bluefeather.json
        COMMENT "Copying config to app bundle"
        VERBATIM
    )
    add_custom_target(copy_config_to_bundle DEPENDS ${HM64_BUNDLE_CONFIG_STAMP})
    add_dependencies(${GAME_SHORT_NAME} copy_config_to_bundle)
endif()

install(TARGETS ${GAME_SHORT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

install(FILES ${HM64_BASE_O2R_FILE}
    DESTINATION share/${GAME_SHORT_NAME}
)

install(FILES ${BLUEFEATHER_PORT_O2R_FILE}
    DESTINATION share/${GAME_SHORT_NAME}
)

install(FILES ${BLUEFEATHER_PROJECT_ROOT}/bluefeather.json
    DESTINATION share/${GAME_SHORT_NAME}
)

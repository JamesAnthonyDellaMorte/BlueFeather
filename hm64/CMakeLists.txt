set(GAME_NAME "Moonwright")
set(GAME_SHORT_NAME "Moonwright")
set(GAME_ASSET_ARCHIVE "${GAME_SHORT_NAME}.o2r")

set(HM64_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(MOONWRIGHT_ROOT ${HM64_ROOT}/moonwright)
set(MOONWRIGHT_PROJECT_ROOT ${HM64_ROOT}/..)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(HM64_PORT_SOURCES
    ${MOONWRIGHT_ROOT}/src/main.cpp
    ${MOONWRIGHT_ROOT}/src/stubs.c
    ${MOONWRIGHT_ROOT}/src/hm64_game.cpp
    ${MOONWRIGHT_ROOT}/src/hm64_gu_compat.c
    ${MOONWRIGHT_ROOT}/src/hm64_ram.cpp
    ${MOONWRIGHT_ROOT}/src/hm64_title_globals.c
    ${MOONWRIGHT_ROOT}/src/nualstl_n.c
    ${MOONWRIGHT_ROOT}/src/nugfx.cpp
    ${MOONWRIGHT_ROOT}/src/ultra64_compat.cpp
    ${MOONWRIGHT_ROOT}/src/ld_symbols.c
)

set(HM64_RUNTIME_SOURCES
    ${HM64_ROOT}/src/mainproc.c
    ${MOONWRIGHT_ROOT}/src/mainLoop.c
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
    ${HM64_ROOT}/src/data/fieldTileMaps/fieldTiles.c
    ${HM64_ROOT}/src/game/gameAudio.c
    ${HM64_ROOT}/src/game/game.c
    ${HM64_ROOT}/src/game/initialize.c
    ${HM64_ROOT}/src/game/gameStart.c
    ${HM64_ROOT}/src/game/level.c
    ${HM64_ROOT}/src/game/npc.c
    ${HM64_ROOT}/src/game/player.c
    ${HM64_ROOT}/src/game/transition.c
    ${HM64_ROOT}/src/game/title.c
    ${HM64_ROOT}/src/game/cutscenes.c
    ${HM64_ROOT}/src/game/animals.c
    ${HM64_ROOT}/src/game/evaluation.c
    ${HM64_ROOT}/src/game/fieldObjects.c
    ${HM64_ROOT}/src/game/gameStatus.c
    ${HM64_ROOT}/src/game/items.c
    ${HM64_ROOT}/src/game/levelInteractions.c
    ${HM64_ROOT}/src/game/load.c
    ${HM64_ROOT}/src/game/time.c
    ${HM64_ROOT}/src/system/audio.c
    ${HM64_ROOT}/src/system/controller.c
    ${HM64_ROOT}/src/system/cutscene.c
    ${HM64_ROOT}/src/system/dialogue.c
    ${HM64_ROOT}/src/system/entity.c
    ${HM64_ROOT}/src/system/flags.c
    ${MOONWRIGHT_ROOT}/src/system/globalSprites.c
    ${MOONWRIGHT_ROOT}/src/system/graphic.c
    ${HM64_ROOT}/src/system/interpolation.c
    ${HM64_ROOT}/src/system/map.c
    ${HM64_ROOT}/src/system/mapController.c
    ${HM64_ROOT}/src/system/math.c
    ${HM64_ROOT}/src/system/memory.c
    ${HM64_ROOT}/src/system/message.c
    ${HM64_ROOT}/src/system/numberSprites.c
    ${HM64_ROOT}/src/system/sceneGraph.c
    ${MOONWRIGHT_ROOT}/src/system/sprite.c
    ${HM64_ROOT}/src/system/spriteDMAManager.c
    ${HM64_ROOT}/src/system/staticGfx.c
    ${HM64_ROOT}/src/data/animationScripts/animationScripts.c
)

set(HM64_COMMON_INCLUDE_DIRS
    ${MOONWRIGHT_ROOT}/src
    ${MOONWRIGHT_ROOT}/include
    ${HM64_ROOT}/include
    ${HM64_ROOT}/src
    ${LIBULTRASHIP_DIR}/include
    ${LIBULTRASHIP_DIR}/include/libultraship
)

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
        MACOSX_BUNDLE_INFO_PLIST ${MOONWRIGHT_PROJECT_ROOT}/CMake/Info.plist.in
        MACOSX_BUNDLE_BUNDLE_NAME "Moonwright"
        MACOSX_BUNDLE_BUNDLE_IDENTIFIER "com.hm64.moonwright"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_LONG_VERSION_STRING "1.0.0"
    )
endif()

set_target_properties(${GAME_SHORT_NAME} PROPERTIES
    OUTPUT_NAME_DEBUG "${GAME_SHORT_NAME}-debug"
)

file(GLOB_RECURSE HM64_ASSET_FILES CONFIGURE_DEPENDS
    "${HM64_ROOT}/assets/sprites/overlayScreens/titleSprites/*"
    "${HM64_ROOT}/assets/sprites/overlayScreens/dialogueButtonIcons/*"
    "${HM64_ROOT}/assets/sprites/entitySprites/animals/dog/*"
    "${HM64_ROOT}/assets/sprites/overlayScreens/logos/*"
    "${HM64_ROOT}/assets/sprites/effects/funeralIntro/*"
    "${HM64_ROOT}/assets/cutscenes/farmBusiness.s"
    "${HM64_ROOT}/assets/cutscenes/funeralIntro.s"
    "${HM64_ROOT}/assets/cutscenes/demos.s"
    "${HM64_ROOT}/assets/audio/sequences/opening.seq"
    "${HM64_ROOT}/assets/audio/sequences/title.seq"
    "${HM64_ROOT}/assets/audio/sequences/spring.seq"
    "${HM64_ROOT}/assets/audio/sequences/namingScreen.seq"
    "${HM64_ROOT}/assets/audio/sequences/mountain.seq"
    "${HM64_ROOT}/assets/audio/sequences/village.seq"
)
file(GLOB_RECURSE HM64_SHADER_FILES CONFIGURE_DEPENDS
    "${LIBULTRASHIP_DIR}/src/fast/shaders/*"
)
file(GLOB_RECURSE HM64_TOOL_FILES CONFIGURE_DEPENDS
    "${HM64_ROOT}/tools/libhm64/*"
)

set(HM64_CUSTOM_ASSET_DIR "${HM64_ROOT}/assets/custom")
set(HM64_CUSTOM_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/stage_custom_assets.stamp")
add_custom_command(
    OUTPUT ${HM64_CUSTOM_ASSET_STAMP}
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${HM64_CUSTOM_ASSET_DIR}
    COMMAND ${Python3_EXECUTABLE}
        ${HM64_ROOT}/tools/build_custom_assets.py
        --output-dir ${HM64_CUSTOM_ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${LIBULTRASHIP_DIR}/src/fast/shaders
        ${HM64_CUSTOM_ASSET_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_CUSTOM_ASSET_STAMP}
    DEPENDS
        ${HM64_ROOT}/tools/build_custom_assets.py
        ${HM64_ASSET_FILES}
        ${HM64_SHADER_FILES}
        ${HM64_TOOL_FILES}
    COMMENT "Staging Moonwright custom assets"
    VERBATIM
)
add_custom_target(StageMoonwrightCustomAssets DEPENDS ${HM64_CUSTOM_ASSET_STAMP})

set(HM64_O2R_FILE "${CMAKE_CURRENT_BINARY_DIR}/${GAME_ASSET_ARCHIVE}")
add_custom_command(
    OUTPUT ${HM64_O2R_FILE}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${HM64_O2R_FILE}
    COMMAND ${Python3_EXECUTABLE}
        ${MOONWRIGHT_PROJECT_ROOT}/OTRExporter/extract_assets.py
        -z "$<TARGET_FILE:ZAPD>"
        --norom
        --custom-otr-file ${HM64_O2R_FILE}
        --custom-assets-path ${HM64_CUSTOM_ASSET_DIR}
    DEPENDS
        ${MOONWRIGHT_PROJECT_ROOT}/OTRExporter/extract_assets.py
        ${HM64_CUSTOM_ASSET_STAMP}
        ZAPD
    WORKING_DIRECTORY ${HM64_ROOT}
    COMMENT "Generating ${GAME_ASSET_ARCHIVE}"
    VERBATIM
)
add_custom_target(GenerateMoonwrightOtr DEPENDS ${HM64_O2R_FILE})
add_dependencies(GenerateMoonwrightOtr StageMoonwrightCustomAssets)
add_dependencies(${GAME_SHORT_NAME} GenerateMoonwrightOtr)

add_custom_target(ExtractAssets DEPENDS ${HM64_O2R_FILE})
add_dependencies(ExtractAssets GenerateMoonwrightOtr)

set(HM64_RUNTIME_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_o2r.stamp")
add_custom_command(
    OUTPUT ${HM64_RUNTIME_ASSET_STAMP}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${HM64_O2R_FILE}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${GAME_ASSET_ARCHIVE}
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_ASSET_STAMP}
    DEPENDS ${HM64_O2R_FILE}
    COMMENT "Copying ${GAME_ASSET_ARCHIVE} to build output"
    VERBATIM
)
add_custom_target(copy_assets DEPENDS ${HM64_RUNTIME_ASSET_STAMP})
add_dependencies(${GAME_SHORT_NAME} copy_assets)

set(HM64_RUNTIME_CONFIG_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_config.stamp")
add_custom_command(
    OUTPUT ${HM64_RUNTIME_CONFIG_STAMP}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MOONWRIGHT_PROJECT_ROOT}/hm64.json
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/hm64.json
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_CONFIG_STAMP}
    DEPENDS ${MOONWRIGHT_PROJECT_ROOT}/hm64.json
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
            ${HM64_O2R_FILE}
            ${APP_RESOURCES}/${GAME_ASSET_ARCHIVE}
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_ASSET_STAMP}
        DEPENDS ${HM64_O2R_FILE}
        COMMENT "Copying ${GAME_ASSET_ARCHIVE} to app bundle"
        VERBATIM
    )
    add_custom_target(copy_assets_to_bundle DEPENDS ${HM64_BUNDLE_ASSET_STAMP})
    add_dependencies(${GAME_SHORT_NAME} copy_assets_to_bundle)

    set(HM64_BUNDLE_CONFIG_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_config_to_bundle.stamp")
    add_custom_command(
        OUTPUT ${HM64_BUNDLE_CONFIG_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${MOONWRIGHT_PROJECT_ROOT}/hm64.json
            ${APP_RESOURCES}/hm64.json
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_CONFIG_STAMP}
        DEPENDS ${MOONWRIGHT_PROJECT_ROOT}/hm64.json
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

install(FILES ${HM64_O2R_FILE}
    DESTINATION share/${GAME_SHORT_NAME}
)

install(FILES ${MOONWRIGHT_PROJECT_ROOT}/hm64.json
    DESTINATION share/${GAME_SHORT_NAME}
)

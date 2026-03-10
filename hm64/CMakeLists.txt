set(GAME_NAME "Moonwright")
set(GAME_SHORT_NAME "Moonwright")

set(HM64_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(MOONWRIGHT_ROOT ${HM64_ROOT}/moonwright)
set(MOONWRIGHT_PROJECT_ROOT ${HM64_ROOT}/..)

set(HM64_PORT_SOURCES
    ${MOONWRIGHT_ROOT}/src/main.cpp
    ${MOONWRIGHT_ROOT}/src/sprite_stubs.c
    ${MOONWRIGHT_ROOT}/src/game_stubs.c
    ${MOONWRIGHT_ROOT}/src/hm64_game.cpp
    ${MOONWRIGHT_ROOT}/src/hm64_gu_compat.c
    ${MOONWRIGHT_ROOT}/src/hm64_host_rom.cpp
    ${MOONWRIGHT_ROOT}/src/hm64_host_shims.c
    ${MOONWRIGHT_ROOT}/src/hm64_ram.cpp
    ${MOONWRIGHT_ROOT}/src/hm64_title_globals.c
    ${MOONWRIGHT_ROOT}/src/hm64_title_runtime.cpp
    ${MOONWRIGHT_ROOT}/src/nugfx.cpp
    ${MOONWRIGHT_ROOT}/src/ultra64_compat.cpp
    ${MOONWRIGHT_ROOT}/src/ld_symbols.c
    ${MOONWRIGHT_ROOT}/src/rom_symbols.c
)

set(HM64_RUNTIME_SOURCES
    ${HM64_ROOT}/src/game/title.c
    ${HM64_ROOT}/src/game/cutscenes.c
    ${HM64_ROOT}/src/system/controller.c
    ${HM64_ROOT}/src/system/cutscene.c
    ${HM64_ROOT}/src/system/flags.c
    ${MOONWRIGHT_ROOT}/src/system/globalSprites.c
    ${MOONWRIGHT_ROOT}/src/system/graphic.c
    ${HM64_ROOT}/src/system/math.c
    ${HM64_ROOT}/src/system/sceneGraph.c
    ${MOONWRIGHT_ROOT}/src/system/sprite.c
    ${HM64_ROOT}/src/system/spriteDMAManager.c
    ${HM64_ROOT}/src/system/staticGfx.c
    ${HM64_ROOT}/src/data/animationScripts/animationScripts.c
)

set(HM64_HOST_CORE_SOURCES
    ${HM64_ROOT}/src/mainproc.c
    ${MOONWRIGHT_ROOT}/src/mainLoop.c
    ${HM64_ROOT}/src/system/controller.c
    ${MOONWRIGHT_ROOT}/src/system/graphic.c
    ${HM64_ROOT}/src/system/staticGfx.c
    ${HM64_ROOT}/src/system/spriteDMAManager.c
    ${HM64_ROOT}/src/system/mapController.c
)

set(HM64_COMMON_INCLUDE_DIRS
    ${MOONWRIGHT_ROOT}/src
    ${MOONWRIGHT_ROOT}/include
    ${HM64_ROOT}/include
    ${HM64_ROOT}/src
    ${LIBULTRASHIP_DIR}/include
    ${LIBULTRASHIP_DIR}/include/libultraship
)

add_library(hm64_decomp_host_core STATIC ${HM64_HOST_CORE_SOURCES})
target_include_directories(hm64_decomp_host_core PRIVATE ${HM64_COMMON_INCLUDE_DIRS})
target_compile_definitions(hm64_decomp_host_core PRIVATE HM64_PC_PORT)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(hm64_decomp_host_core
        PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
            -Wno-unused-variable
            -Wno-incompatible-function-pointer-types
    )
endif()

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
    "${HM64_ROOT}/assets/*"
)
file(GLOB_RECURSE HM64_SHADER_FILES CONFIGURE_DEPENDS
    "${LIBULTRASHIP_DIR}/src/fast/shaders/*"
)

set(HM64_RUNTIME_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_assets.stamp")
add_custom_command(
    OUTPUT ${HM64_RUNTIME_ASSET_STAMP}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${HM64_ROOT}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${LIBULTRASHIP_DIR}/src/fast/shaders
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/shaders
    COMMAND ${CMAKE_COMMAND} -E touch ${HM64_RUNTIME_ASSET_STAMP}
    DEPENDS ${HM64_ASSET_FILES} ${HM64_SHADER_FILES}
    COMMENT "Copying assets and libultraship shaders to build directory"
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

    set(HM64_BUNDLE_ASSET_STAMP "${CMAKE_CURRENT_BINARY_DIR}/copy_assets_to_bundle.stamp")
    add_custom_command(
        OUTPUT ${HM64_BUNDLE_ASSET_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${HM64_ROOT}/assets
            ${APP_RESOURCES}/assets
        COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_RESOURCES}/assets/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${LIBULTRASHIP_DIR}/src/fast/shaders
            ${APP_RESOURCES}/assets/shaders
        COMMAND ${CMAKE_COMMAND} -E touch ${HM64_BUNDLE_ASSET_STAMP}
        DEPENDS ${HM64_ASSET_FILES} ${HM64_SHADER_FILES}
        COMMENT "Copying assets and libultraship shaders to app bundle"
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

install(DIRECTORY ${HM64_ROOT}/assets
    DESTINATION share/${GAME_SHORT_NAME}
)

install(FILES ${MOONWRIGHT_PROJECT_ROOT}/hm64.json
    DESTINATION share/${GAME_SHORT_NAME}
)

# Keep Homebrew/system spdlog packages out of this build so libultraship
# can use the dependency version it expects.
list(APPEND CMAKE_IGNORE_PATH
    "/opt/homebrew/lib/cmake/spdlog"
    "/opt/homebrew/opt/spdlog/lib/cmake/spdlog"
    "/usr/local/lib/cmake/spdlog")

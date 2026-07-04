cmake_minimum_required(VERSION 3.21)
project(PixelEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.12
    GIT_SHALLOW TRUE
)
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.4.4
    GIT_SHALLOW TRUE
)

set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)
FetchContent_MakeAvailable(SDL3_image)

add_executable(PixelEngine
    game/main.cpp
    engine/core/Engine.cpp
    engine/core/Time.cpp
    engine/core/states/BootState.cpp
    engine/core/states/ShutDownState.cpp
    engine/core/states/RunningState.cpp
    engine/renderer/Renderer.cpp
    engine/renderer/TextureManager.cpp
    engine/assets/AssetManager.cpp
)

target_include_directories(PixelEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/engine
)

target_link_libraries(PixelEngine PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

add_custom_command(TARGET PixelEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DBUILD_DIR=${CMAKE_BINARY_DIR}
        -DDEST_DIR=$<TARGET_FILE_DIR:PixelEngine>
        -P ${CMAKE_SOURCE_DIR}/cmake/CopyRuntimeDlls.cmake
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/game/assets
        $<TARGET_FILE_DIR:PixelEngine>/assets
)
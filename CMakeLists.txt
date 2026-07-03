cmake_minimum_required(VERSION 3.20)
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

set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

add_executable(PixelEngine
    game/main.cpp
)

target_link_libraries(PixelEngine PRIVATE SDL3::SDL3)

add_custom_command(TARGET PixelEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:PixelEngine>
)
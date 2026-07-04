#pragma once

#include <SDL3/SDL.h>

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect sourceRect{};
};
#pragma once

#include <SDL3/SDL.h>

struct Sprite {
    SDL_Texture* texture = nullptr;
    float x = 0.0f;
    float y = 0.0f;
};
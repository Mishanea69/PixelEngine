#pragma once

#include <SDL3/SDL.h>

static constexpr float ReferenceUnitsPerPixel = 32.0f; // Reference units per pixel for scaling

struct Anchor {
    float x = 0.0f; // Horizontal anchor point (0.0 = left, 1.0 = right)
    float y = 0.0f; // Vertical anchor point (0.0 = top, 1.0 = bottom)
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect sourceRect{};
    Anchor anchor{};
    float pixelsPerUnit = ReferenceUnitsPerPixel;
};
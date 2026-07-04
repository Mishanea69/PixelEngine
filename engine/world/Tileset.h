#pragma once

#include <SDL3/SDL.h>

struct TileSet {
    SDL_Texture* texture = nullptr;
    int tileWidth = 0;
    int tileHeight = 0;
    int columns = 0;
    int firstGid = 1;

    SDL_FRect GetSourceRect(int index) const {
        int localId = index - firstGid;
        int col = localId % columns;
        int row = localId / columns;
        return SDL_FRect{
            static_cast<float>(col * tileWidth),
            static_cast<float>(row * tileHeight),
            static_cast<float>(tileWidth),
            static_cast<float>(tileHeight)
        };
    }
};
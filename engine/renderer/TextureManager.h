#pragma once

#include <SDL3/SDL.h>
#include <assets/AssetManager.h>
#include <memory>
#include <string>
#include <unordered_map>

struct SdlTextureDestroyer {
    void operator()(SDL_Texture* t) const { SDL_DestroyTexture(t); }
};
using TexturePtr = std::unique_ptr<SDL_Texture, SdlTextureDestroyer>;

class TextureManager {
    SDL_Renderer* renderer = nullptr;
    AssetManager* assetManager = nullptr;
    std::unordered_map<std::string, TexturePtr> cache;

public:
    TextureManager() = default;
    ~TextureManager() = default;

    void Init(SDL_Renderer* r, AssetManager* am) {
        renderer = r;
        assetManager = am;
    }

    SDL_Texture* LoadTexture(const std::string& assetPath);

};
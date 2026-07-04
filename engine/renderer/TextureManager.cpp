#include <renderer/TextureManager.h>
#include <assets/AssetManager.h>
#include <SDL3_image/SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const std::string& assetPath) {
    std::string filePath = assetManager->GetAssetPath(assetPath);

    // Check if the texture is already in the cache
    auto it = cache.find(filePath);
    if (it != cache.end()) {
        return it->second.get();
    }

    // Load the texture from file
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        SDL_Log("Failed to load texture %s: %s", filePath.c_str(), SDL_GetError());
        return nullptr;
    }

    // Set the texture scale mode to nearest neighbor for pixel art
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    // Store the texture in the cache
    cache[filePath] = TexturePtr(texture);

    return texture;
}
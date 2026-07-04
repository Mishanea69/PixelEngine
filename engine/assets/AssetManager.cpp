#include <assets/AssetManager.h>
#include <SDL3/SDL.h>

bool AssetManager::Init() {
    // Set the asset directory to the "assets" folder in the current working directory
    if (SDL_GetBasePath() != nullptr) {
        std::string basePath(SDL_GetBasePath());
        assetDirectory = basePath + "assets/";
    } else {
        SDL_Log("Failed to get base path: %s", SDL_GetError());
        return false;
    }

    return true;
}

std::string AssetManager::GetAssetPath(const std::string& relativePath) const {
    return assetDirectory + relativePath;
}
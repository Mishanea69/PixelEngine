#pragma once

#include <string>

class AssetManager {
    std::string assetDirectory;

public:
    bool Init();
    std::string GetAssetPath(const std::string& relativePath) const;

};
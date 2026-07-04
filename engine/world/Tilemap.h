#pragma once

#include <world/Tileset.h>
#include <renderer/Renderer.h>
#include <renderer/TextureManager.h>
#include <assets/AssetManager.h>
#include <vector>
#include <string>

struct TileLayer {
    std::vector<int> tiles;
};

class TileMap {
public:
    bool Load(AssetManager& assetManager, TextureManager& textureManager, const std::string mapPath);
    void Render(Renderer& renderer) const;

    int width = 0;
    int height = 0;
    TileSet tileset;
    std::vector<TileLayer> layers;
};
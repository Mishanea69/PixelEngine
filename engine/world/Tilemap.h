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
    bool Bake(Renderer&);
    TexturePtr bakedTexture;

public:
    bool Load(AssetManager& assetManager, TextureManager& textureManager, Renderer& renderer, const std::string mapPath);
    void Render(Renderer& renderer) const;

    int width = 0;
    int height = 0;
    TileSet tileset;
    std::vector<TileLayer> layers;
};
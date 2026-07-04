#include <world/Tilemap.h>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;

bool TileMap::Load(AssetManager& assetManager, TextureManager& textureManager, const std::string mapPath){
    std::string path = assetManager.GetAssetPath(mapPath);
    std::ifstream file(path);
    if (!file.is_open()){
        SDL_Log("TileMap: failed to open %s", path.c_str());
        return false;
    }

    try {
        json data = json::parse(file);

        width = data["width"].get<int>();
        height = data["height"].get<int>();
        
        // Tilesheet data:
        tileset.tileWidth = data["tilesets"][0]["tilewidth"].get<int>();
        tileset.tileHeight = data["tilesets"][0]["tileheight"].get<int>();
        tileset.columns = data["tilesets"][0]["columns"].get<int>();
        tileset.firstGid = data["tilesets"][0]["firstgid"].get<int>();
        
        std::string tilesetImage = data["tilesets"][0]["image"].get<std::string>();
        size_t splitPos = tilesetImage.find_last_of('/');
        if (splitPos != std::string::npos) {
            tilesetImage = tilesetImage.substr(splitPos + 1);
        }
        size_t mapDirPos = mapPath.find_last_of('/');
        std::string mapDir = (mapDirPos != std::string::npos) ? mapPath.substr(0, mapDirPos + 1) : "";
        tileset.texture = textureManager.LoadTexture(mapDir + tilesetImage);


        //Layers data:
        for (const auto& layerData : data["layers"]){
            TileLayer layer;
            layer.tiles = layerData["data"].get<std::vector<int>>();
            layers.push_back(layer);
        }

    } catch (const json::exception& e) {
        SDL_Log("TileMap: JSON parsing error in %s: %s", path.c_str(), e.what());
        return false;
    }

    return true;
}

void TileMap::Render(Renderer& renderer) const {
    for(const auto& layer : layers){
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                int index = y * width + x;
                int tileId = layer.tiles[index];
                if(tileId > 0){
                    SDL_FRect sourceRect = tileset.GetSourceRect(tileId);
                    SDL_FRect destRect{
                        static_cast<float>(x * tileset.tileWidth),
                        static_cast<float>(y * tileset.tileHeight),
                        static_cast<float>(tileset.tileWidth),
                        static_cast<float>(tileset.tileHeight)
                    };
                    renderer.DrawSprite({tileset.texture, sourceRect}, {destRect.x, destRect.y});
                }
            }
        }
    }
}
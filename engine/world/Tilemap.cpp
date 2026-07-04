#include <world/Tilemap.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
using json = nlohmann::json;

bool TileMap::Load(AssetManager& assetManager, TextureManager& textureManager, Renderer& renderer, const std::string mapPath){
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

    if(!Bake(renderer)){
        SDL_Log("TileMap: failed to bake tilemap");
        return false;
    }

    return true;
}

bool TileMap::Bake(Renderer& renderer) {
    int pixelWidth = width * tileset.tileWidth;
    int pixelHeight = height * tileset.tileHeight;

    bakedTexture = TexturePtr(SDL_CreateTexture(renderer.Get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pixelWidth, pixelHeight));
    if (!bakedTexture) {
        SDL_Log("TileMap: failed to create baked texture");
        return false;
    }

    Uint8 savedR, savedG, savedB, savedA;
    SDL_GetRenderDrawColor(renderer.Get(), &savedR, &savedG, &savedB, &savedA);

    SDL_SetTextureScaleMode(bakedTexture.get(), SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(bakedTexture.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer.Get(), bakedTexture.get());
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 0);
    SDL_RenderClear(renderer.Get());

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
   
    SDL_SetRenderTarget(renderer.Get(), nullptr);
    SDL_SetRenderDrawColor(renderer.Get(), savedR, savedG, savedB, savedA);
    return true;
}

void TileMap::Render(Renderer& renderer) const {
    if(bakedTexture) renderer.DrawSprite(Sprite{bakedTexture.get()}, Transform{0.0f, 0.0f});
}
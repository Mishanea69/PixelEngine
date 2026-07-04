#pragma once

class Renderer;
class TextureManager;
class AssetManager;

struct EngineContext {
    Renderer& renderer;
    TextureManager& textureManager;
    AssetManager& assetManager;
};
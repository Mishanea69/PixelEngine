#pragma once

#include <renderer/Renderer.h>
#include <renderer/TextureManager.h>
#include <assets/AssetManager.h>
#include <input/InputManager.h>

struct EngineContext {
    Renderer& renderer;
    TextureManager& textureManager;
    AssetManager& assetManager;
    InputManager& inputManager;
};
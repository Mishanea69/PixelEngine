#pragma once

#include <core/GameState.h>
#include <entity/Entity.h>
#include <world/Tilemap.h>

class RunningState : public GameState {
    Entity heart;
    TileMap tileMap;
public:
    void OnEnter(EngineContext& ctx) override;
    void OnExit(EngineContext& ctx) override;
    void Update(EngineContext& ctx, double dt) override;
    void FixedUpdate(EngineContext& ctx, double dt) override;
    void Render(EngineContext& ctx, double alpha) override;
};
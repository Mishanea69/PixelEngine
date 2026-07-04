#pragma once

#include <core/GameState.h>
#include <renderer/Sprite.h>

class RunningState : public GameState {
    Sprite heartSprite;
public:
    void OnEnter(EngineContext& ctx) override;
    void OnExit(EngineContext& ctx) override;
    void Update(EngineContext& ctx, double dt) override;
    void Render(EngineContext& ctx, double alpha) override;
};
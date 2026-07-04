#pragma once

#include <core/GameState.h>

class BootState : public GameState { 
public: 
    void OnEnter(EngineContext& ctx) override; 
    void OnExit(EngineContext& ctx) override;
    void Update(EngineContext& ctx, double dt) override;
    void FixedUpdate(EngineContext& ctx, double dt) override;
    void Render(EngineContext& ctx, double alpha) override;
};
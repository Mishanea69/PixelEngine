#pragma once

struct EngineContext;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void OnEnter(EngineContext& ctx) {}
    virtual void OnExit(EngineContext& ctx) {}
    virtual void Update(EngineContext& ctx, double dt) {}
    virtual void Render(EngineContext& ctx, double alpha) {}
};
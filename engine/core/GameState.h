#pragma once

struct SDL_Renderer;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void OnEnter() {}
    virtual void OnExit() {}
    virtual void Update(double dt) {}
    virtual void Render(SDL_Renderer* renderer, double alpha) {}
};
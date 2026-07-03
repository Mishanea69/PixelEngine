#pragma once

#include <core/GameState.h>

class RunningState : public GameState {
public:
    void OnEnter() override;
    void OnExit() override;
    void Update(double dt) override;
    void Render(SDL_Renderer* renderer, double alpha) override;
};
#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class InputManager {
    std::unordered_map<std::string, SDL_Scancode> bindings;
    std::vector<bool> currentKeyStates;
    std::vector<bool> previousKeyStates;

    int KeyResolution(std::string key);

public:
    InputManager() = default;
    ~InputManager() = default;

    void Update();
    void BindKey(const std::string& action, SDL_Scancode key);
    void BindKey(const std::string& action, std::string key);

    bool IsKeyHeld(std::string key);
    bool IsKeyPressed(std::string key);
    bool IsKeyReleased(std::string key);

    bool IsActionHeld(const std::string& action);
    bool IsActionPressed(const std::string& action);
    bool IsActionReleased(const std::string& action);
};
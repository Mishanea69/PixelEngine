#include <input/InputManager.h>
#include <algorithm>

void InputManager::Update() {
    int numKeys;
    const bool* keyStates = SDL_GetKeyboardState(&numKeys);

    // Resize the key state vectors if necessary
    if (previousKeyStates.size() != static_cast<size_t>(numKeys)) {
        previousKeyStates.resize(numKeys, false);
        currentKeyStates.resize(numKeys, false);
    }

    // Update the key states
    previousKeyStates = currentKeyStates;
    currentKeyStates.assign(keyStates, keyStates + numKeys);
}

void InputManager::BindKey(const std::string& action, SDL_Scancode key) {
    bindings[action] = key;
}
void InputManager::BindKey(const std::string& action, std::string key) {
    bindings[action] = static_cast<SDL_Scancode>(KeyResolution(key));
}

bool InputManager::IsActionHeld(const std::string& action) {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        int keycode = it->second;
        return currentKeyStates[keycode];
    }
    return false;
}

bool InputManager::IsActionPressed(const std::string& action) {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        int keycode = it->second;
        return currentKeyStates[keycode] && !previousKeyStates[keycode];
    }
    return false;
}

bool InputManager::IsActionReleased(const std::string& action) {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        int keycode = it->second;
        return !currentKeyStates[keycode] && previousKeyStates[keycode];
    }
    return false;
}

bool InputManager::IsKeyHeld(std::string key) {
    int keycode = KeyResolution(key);
    return currentKeyStates[keycode];
}

bool InputManager::IsKeyPressed(std::string key) {
    int keycode = KeyResolution(key);
    return currentKeyStates[keycode] && !previousKeyStates[keycode];
}

bool InputManager::IsKeyReleased(std::string key) {
    int keycode = KeyResolution(key);
    return !currentKeyStates[keycode] && previousKeyStates[keycode];
}



// void InputManager::HandleEvent(const SDL_Event& event) {
//     // Handle input events
// }


// == Helper Funtions =============================================================================================================

int InputManager::KeyResolution(std::string key) {
    // Convert string representation of key to SDL_Scancode
    // 1. convert to lowwercase
    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });

    if (key.length() == 1) {
        char c = key[0];
        if (c >= 'a' && c <= 'z') {
            return SDL_SCANCODE_A + (c - 'a');
        }

        if (c >= '1' && c <= '9') {
            return SDL_SCANCODE_1 + (c - '1'); // Map '1'-'9' to SDL_SCANCODE_1 - SDL_SCANCODE_9
        } else if (c == '0') {
            return SDL_SCANCODE_0; // Map '0' to SDL_SCANCODE_0
        }
    } else {
        // Handle special keys
    }


    SDL_Log("KeyResolution: Unrecognized key string '%s'", key.c_str());
    return 0; 
}
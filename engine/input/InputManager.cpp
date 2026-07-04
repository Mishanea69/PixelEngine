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
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        for(SDL_Scancode scancode : it->second){
            if (key == scancode){
                SDL_Log("InputManager: key <%s> already binded to action [%s]", SDL_GetScancodeName(key), action.c_str());
                return;
            }
        }
        SDL_Log("InputManager: Binded key<%s> to action [%s]", SDL_GetScancodeName(key), action.c_str());
        it->second.push_back(key);
    } else {
        SDL_Log("InputManager: Binded key<%s> to action [%s]", SDL_GetScancodeName(key), action.c_str());
        bindings[action] = {key};
    }
}
void InputManager::BindKey(const std::string& action, std::string key) {
    BindKey(action, static_cast<SDL_Scancode>(KeyResolution(key)));
}

bool InputManager::IsActionHeld(const std::string& action) {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        for (SDL_Scancode scancode : it->second) {
            if (currentKeyStates[scancode]) {
                return true;
            }
        }
    }
    return false;
}

bool InputManager::IsActionPressed(const std::string& action) {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        for (SDL_Scancode scancode : it->second) {
            if (currentKeyStates[scancode] && !previousKeyStates[scancode]) {
                return true;
            }
        }
    }
    return false;
}

bool InputManager::IsActionReleased(const std::string& action) {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        for (SDL_Scancode scancode : it->second) {
            if (!currentKeyStates[scancode] && previousKeyStates[scancode]) {
                return true;
            }
        }
    }
    return false;
}


// == Helper Funtions =============================================================================================================

int InputManager::KeyResolution(std::string key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        // Check custom names:
        std::string initialKey = key;
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    
        if(key == "SPACE") return SDL_SCANCODE_SPACE;
        if(key == "ESC" || key == "ESCAPE") return SDL_SCANCODE_ESCAPE;
        if(key == "CTRL" || key == "CONTROL") return SDL_SCANCODE_LCTRL;
        if(key == "SHIFT") return SDL_SCANCODE_LSHIFT;
        if(key == "TAB") return SDL_SCANCODE_TAB;
        if(key == "CAPS" || key == "CAPSLOCK") return SDL_SCANCODE_CAPSLOCK;
        if(key == "UP" || key == "ARROW_UP") return SDL_SCANCODE_UP;
        if(key == "DOWN" || key == "ARROW_DOWN") return SDL_SCANCODE_DOWN;
        if(key == "LEFT" || key == "ARROW_LEFT") return SDL_SCANCODE_LEFT;
        if(key == "RIGHT" || key == "ARROW_RIGHT") return SDL_SCANCODE_RIGHT;

        SDL_Log("KeyResolution: Unrecognized key string '%s'", initialKey.c_str());
    }

    return scancode; 
}
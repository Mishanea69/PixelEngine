#pragma once

struct Camera {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    void Follow(float targetX, float targetY, float dt, float smoothing) {
        float targetCameraX = targetX - width / 2.0f;
        float targetCameraY = targetY - height / 2.0f;

        x += (targetCameraX - x) * smoothing * dt;
        y += (targetCameraY - y) * smoothing * dt;
    }
};
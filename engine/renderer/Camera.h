#pragma once

struct Camera {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float followTargetX = 0.0f;
    float followTargetY = 0.0f;
    float zoom = 1.0f;

    void Follow(float targetX, float targetY, double dt, float smoothing) {
        followTargetX = targetX;
        followTargetY = targetY;

        float visibleWidth = width / zoom;
        float visibleHeight = height / zoom;
        float targetCameraX = targetX - visibleWidth / 2.0f;
        float targetCameraY = targetY - visibleHeight / 2.0f;

        x += (targetCameraX - x) * smoothing * dt;
        y += (targetCameraY - y) * smoothing * dt;
    }

    void SetZoom(float newZoom) {
        if (newZoom <= 0.0f) newZoom = 0.25f; // Prevent zoom from being zero or negative
        if (newZoom > 4.0f) newZoom = 4.0f; // Limit maximum zoom level
        zoom = newZoom;

        // Snap immediately instead of drifting through the lerp — zoom changes
        // should feel instant, unlike normal movement-follow smoothing.
        float visibleWidth = width / zoom;
        float visibleHeight = height / zoom;
        x = followTargetX - visibleWidth / 2.0f;
        y = followTargetY - visibleHeight / 2.0f;
    }
};
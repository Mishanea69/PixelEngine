#pragma once

#include <entity/Transform.h>
#include <renderer/Sprite.h>
#include <optional>

struct Entity{
    Transform transform;
    std::optional<Sprite> sprite;
};
#pragma once

#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    TransformComponent()
        : Position(0.0f), Rotation(0.0f), Scale(1.0f) {}

    TransformComponent(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
        : Position(pos), Rotation(rot), Scale(scale) {}
};

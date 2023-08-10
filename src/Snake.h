#pragma once

#include "Entity.h"

enum class MovementDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

class Snake : public Entity
{
public:
    Snake(const std::string& name, const StaticMesh& staticMesh)
        : Entity(name, staticMesh), BodySize(1) {}

    Snake(const std::string& name, const StaticMesh& staticMesh, const glm::vec3& initialPos, const glm::vec3& initialRot, const glm::vec3& initialScale)
        : Entity(name, staticMesh, initialPos, initialRot, initialScale), BodySize(1) {}

    void Update(float deltaTime) override;

    uint32_t BodySize;

private:
    // Movement variables
    float velocity = 1.0f;
    MovementDirection direction = MovementDirection::DOWN;
};

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
        : Entity(name, staticMesh) {}

    void Update(float deltaTime) override;

private:
    // Movement variables
    float velocity = 1.0f;
    MovementDirection direction = MovementDirection::DOWN;
};

#pragma once

#include "Entity.h"

class Food : public Entity
{
public:
    Food(const std::string& name, const StaticMesh& staticMesh)
        : Entity(name, staticMesh) {}

    Food(const std::string& name, const StaticMesh& staticMesh, const glm::vec3& initialPos, const glm::vec3& initialRot, const glm::vec3& initialScale)
        : Entity(name, staticMesh, initialPos, initialRot, initialScale) {}

    void Spawn();

};

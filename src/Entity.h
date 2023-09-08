#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <chrono>

#include "StaticMesh.h"
#include "TransformComponent.h"

class Entity
{
public:
    Entity(const std::string& name, const StaticMesh& staticMesh, bool isVisible = true)
        : Name(name), Mesh(staticMesh), Transform(), ModelMatrix(1.0f), IsVisible(isVisible) {}

    Entity(const std::string& name, const StaticMesh& staticMesh, const glm::vec3& initialPos, const glm::vec3& initialRot, const glm::vec3& initialScale, bool isVisible = true)
        : Name(name), Mesh(staticMesh), Transform(initialPos, initialRot, initialScale), ModelMatrix(1.0f), IsVisible(isVisible) {}

    virtual void Update(float deltaTime);

    std::string Name;
    StaticMesh Mesh;
    TransformComponent Transform;
    bool IsVisible;

    glm::mat4 ModelMatrix;
};

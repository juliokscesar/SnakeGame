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
    Entity(const std::string& name, const StaticMesh& staticMesh)
        : Name(name), Mesh(staticMesh), Transform(), ModelMatrix(1.0f) {}

    Entity(const std::string& name, const StaticMesh& staticMesh, const glm::vec3& initialPos, const glm::vec3& initialRot, const glm::vec3& initialScale)
        : Name(name), Mesh(staticMesh), Transform(initialPos, initialRot, initialScale), ModelMatrix(1.0f) {}

    virtual void Update(float deltaTime);

    std::string Name;
    StaticMesh Mesh;
    TransformComponent Transform;
    
    glm::mat4 ModelMatrix;
};

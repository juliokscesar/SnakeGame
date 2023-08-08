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

    virtual void Update(float deltaTime);

    std::string Name;
    StaticMesh Mesh;
    TransformComponent Transform;
    
    glm::mat4 ModelMatrix;
};

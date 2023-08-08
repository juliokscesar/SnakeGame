#pragma once

#include <vector>
#include "Entity.h"

class UIEntityManager
{
public:
    UIEntityManager(const std::vector<Entity*>& entityDB)
        : m_entityDB(entityDB), m_selectedEntity(nullptr) {}

    void Draw(float deltaTime);

private:
    const std::vector<Entity*>& m_entityDB;

    Entity* m_selectedEntity;
};

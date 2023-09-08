#pragma once

#include <vector>
#include "Entity.h"

class UIEntityManager
{
public:
    UIEntityManager(std::vector<Entity*>& entityDB)
        : m_entityDB(entityDB), m_selectedEntity(nullptr), m_selectedEntityIndex(0) {}

    void Draw(float deltaTime);

private:
    std::vector<Entity*>& m_entityDB;

    Entity* m_selectedEntity;
    size_t m_selectedEntityIndex;
};

#include "UIEntityManager.h"

#include <imgui/imgui.h>

void UIEntityManager::Draw(float deltaTime)
{
    ImGui::Begin("Entity Manager");

    ImGui::Text("FPS: %f", (1.0f / deltaTime));

    for (Entity *entity : m_entityDB)
    {
        if (ImGui::Button(entity->Name.c_str()))
            m_selectedEntity = entity;
    }


    if (m_selectedEntity)
    {
        ImGui::Text("Position");
        ImGui::InputFloat("X##pos", &m_selectedEntity->Transform.Position.x, 0.1f, 100.0f);
        ImGui::InputFloat("Y##pos", &m_selectedEntity->Transform.Position.y, 0.1f, 100.0f);
        ImGui::InputFloat("Z##pos", &m_selectedEntity->Transform.Position.z, 0.1f, 100.0f);

        ImGui::Text("Rotation");
        ImGui::InputFloat("X##rot", &m_selectedEntity->Transform.Rotation.x, 0.1f, 100.0f);
        ImGui::InputFloat("Y##rot", &m_selectedEntity->Transform.Rotation.y, 0.1f, 100.0f);
        ImGui::InputFloat("Z##rot", &m_selectedEntity->Transform.Rotation.z, 0.1f, 100.0f);

        ImGui::Text("Scale");
        ImGui::InputFloat("X##scale", &m_selectedEntity->Transform.Scale.x, 0.1f, 100.0f);
        ImGui::InputFloat("Y##scale", &m_selectedEntity->Transform.Scale.y, 0.1f, 100.0f);
        ImGui::InputFloat("Z##scale", &m_selectedEntity->Transform.Scale.z, 0.1f, 100.0f);
    }

    ImGui::End();
}

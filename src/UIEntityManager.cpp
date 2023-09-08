#include "UIEntityManager.h"

#include <imgui/imgui.h>

void UIEntityManager::Draw(float deltaTime)
{
    ImGui::Begin("Entity Manager");

    ImGui::Text("FPS: %f", (1.0f / deltaTime));

    for (size_t i = 0, n = m_entityDB.size(); i < n; i++)
    {
        if (ImGui::Button(m_entityDB[i]->Name.c_str()))
        {
            m_selectedEntity = m_entityDB[i];
            m_selectedEntityIndex = i;
        }
        ImGui::SameLine();
    }
    ImGui::NewLine();

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

        ImGui::Checkbox("Is Visible", &(m_selectedEntity->IsVisible));

        if (ImGui::Button("Delete"))
        {
            m_entityDB.erase(m_entityDB.begin() + m_selectedEntityIndex);
            m_selectedEntity = nullptr;
        }
    }

    ImGui::End();
}

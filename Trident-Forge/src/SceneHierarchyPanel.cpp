#include "SceneHierarchyPanel.h"

#include <imgui.h>

SceneHierarchyPanel::SceneHierarchyPanel(Engine::Scene* scene) { SetContext(scene); }

void SceneHierarchyPanel::SetContext(Engine::Scene* scene)
{
    m_Context = scene;
    m_SelectedEntity = Engine::kInvalidEntity;
}

void SceneHierarchyPanel::OnImGuiRender()
{
    ImGui::Begin("Scene Hierarchy");
    if (m_Context)
    {
        m_Context->ForEach<Engine::TagComponent>([&](Engine::Entity entity, Engine::TagComponent& tag)
            { 
                DrawEntityNode(entity); 
            });

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            m_SelectedEntity = Engine::kInvalidEntity;
        }
    }
    ImGui::End();
}

void SceneHierarchyPanel::DrawEntityNode(Engine::Entity entity)
{
    auto& tag = entity.GetComponent<Engine::TagComponent>().Tag;
    ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity.GetHandle(), flags, tag.c_str());

    if (ImGui::IsItemClicked())
    {
        m_SelectedEntity = entity;
    }

    if (opened)
    {
        ImGui::TreePop();
    }
}
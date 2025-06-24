#pragma once

#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "ECS/Scene.h"

#include <Core.h>

class SceneHierarchyPanel
{
  public:
    SceneHierarchyPanel() = default;
    SceneHierarchyPanel(Engine::Scene *scene);

    void SetContext(Engine::Scene *scene);
    void OnImGuiRender();

    Engine::Entity GetSelectedEntity() const { return m_SelectedEntity; }
    void SetSelectedEntity(Engine::Entity entity) { m_SelectedEntity = entity; }

  private:
    void DrawEntityNode(Engine::Entity entity);

    Engine::Scene *m_Context{nullptr};
    Engine::Entity m_SelectedEntity{Engine::kInvalidEntity};
};
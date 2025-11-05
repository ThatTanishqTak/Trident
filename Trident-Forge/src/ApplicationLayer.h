#pragma once

#include <Core.h>

#include "ECS/Components.h"
#include "ECS/Scene.h"

#include "SceneHierarchyPanel.h"
#include "ContentBrowserPanel.h"

#include <glm/gtc/matrix_transform.hpp>

class ApplicationLayer
{
public:
    ApplicationLayer(const std::shared_ptr<Engine::Framebuffer>& framebuffer,
        const std::shared_ptr<Engine::EditorCamera>& camera,
        const std::shared_ptr<Engine::WindowsWindow>& window, int& width, int& height);

    void Init();
    void OnEvent(Engine::Event& e);
    void RenderScene();
    void RenderUI();

    Engine::Entity SpawnCube(const glm::vec3& position);
    Engine::Entity SpawnSphere(const glm::vec3& position);
    glm::vec3 ScreenToWorld(float mouseX, float mouseY) const;

    // The editor and runtime can use this accessor to wire systems, including the
    // new physics stepper, without breaking the layer encapsulation. Returning a
    // reference keeps ownership inside the layer but gives callers full access.
    Engine::Scene& GetScene() { return m_Scene; }
    const Engine::Scene& GetScene() const { return m_Scene; }

private:
    std::shared_ptr<Engine::Framebuffer> m_SceneFramebuffer;
    std::shared_ptr<Engine::EditorCamera> m_Camera;
    std::shared_ptr<Engine::WindowsWindow> m_Window;

    glm::vec3 m_CubePosition{ 0.0f };
    Engine::Scene m_Scene;
    Engine::Entity m_SelectedEntity{ Engine::kInvalidEntity };
    SceneHierarchyPanel m_SceneHierarchyPanel;
    ContentBrowserPanel m_ContentBrowserPanel;

    Engine::Entity m_LightEntity{ Engine::kInvalidEntity };

    glm::vec3 m_CameraPosition{ 0.0f };

    glm::vec4 m_Color{ 1.0f };

    int& m_Width;
    int& m_Height;
};
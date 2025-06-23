#pragma once

#include <Core.h>

#include "ECS/Scene.h"
#include "ECS/Components.h"

#include <glm/gtc/matrix_transform.hpp>

class ApplicationLayer
{
public:
    ApplicationLayer(const std::shared_ptr<Engine::Framebuffer>& framebuffer, const std::shared_ptr<Engine::CameraController>& cameraController,
                     const std::shared_ptr<Engine::WindowsWindow>& window, int& width, int& height);

    void Init();
    void OnEvent(Engine::Event& e);
    void RenderScene();
    void RenderUI();

    Engine::Entity SpawnCube(const glm::vec3& position);
    glm::vec3 ScreenToWorld(float mouseX, float mouseY) const;

private:
    std::shared_ptr<Engine::Framebuffer> m_SceneFramebuffer;
    std::shared_ptr<Engine::CameraController> m_CameraController;
    std::shared_ptr<Engine::WindowsWindow> m_Window;

    glm::vec3 m_CubePosition{ 0.0f };
    Engine::Scene m_Scene;
    Engine::Entity m_SelectedEntity{ Engine::kInvalidEntity };

    glm::vec3 m_LightPosition{ 2.0f, 4.0f, 2.0f };
    glm::vec3 m_LightColor{ 1.0f };
    float m_LightIntensity{ 1.0f };

    glm::vec3 m_CameraPosition{ 0.0f };

    glm::vec4 m_Color{ 1.0f };

    int& m_Width;
    int& m_Height;
};
#pragma once

#include <Core.h>

#include "ECS/Scene.h"
#include "ECS/Components.h"

class ApplicationLayer
{
public:
    ApplicationLayer(const std::shared_ptr<Engine::Framebuffer>& framebuffer, const std::shared_ptr<Engine::CameraController>& cameraController,
                     const std::shared_ptr<Engine::WindowsWindow>& window, int& width, int& height);

    void Init();
    void OnEvent(Engine::Event& e);
    void RenderScene();
    void RenderUI();

private:
    std::shared_ptr<Engine::Framebuffer> m_SceneFramebuffer;
    std::shared_ptr<Engine::CameraController> m_CameraController;
    std::shared_ptr<Engine::WindowsWindow> m_Window;

    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Shader> m_Shader;

    glm::vec3 m_CubePosition{ 0.0f };
    Engine::Scene m_Scene;
    Engine::Entity m_CubeEntity{ Engine::kInvalidEntity };

    glm::vec3 m_LightPosition{ 2.0f, 4.0f, 2.0f };
    glm::vec3 m_LightColor{ 1.0f };
    float m_LightIntensity{ 1.0f };

    glm::vec3 m_CameraPosition{ 0.0f };

    int& m_Width;
    int& m_Height;
};
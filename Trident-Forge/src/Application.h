#pragma once

#include <Core.h>

class Application
{
public:
    Application();
    ~Application();

    static Application& Get();
    void Run();

private:
    void Init();
    void Shutdown();
    void RenderUI();
    void RenderScene();

    void OnEvent(Engine::Event& e);

private:
    static Application* s_Instance;

    std::shared_ptr<Engine::WindowsWindow> m_Window;

    std::shared_ptr<Engine::Renderer> m_Renderer;
    std::shared_ptr<Engine::Framebuffer> m_SceneFramebuffer;
    std::shared_ptr<Engine::RenderPass> m_RenderPass;
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Shader> m_Shader;

    std::shared_ptr<Engine::CameraController> m_CameraController;
    std::unique_ptr<Engine::PerspectiveCamera> m_Camera;

    std::unique_ptr<Engine::ImGuiLayer> m_ImGuiLayer;

    int m_Width = 1920;
    int m_Height = 1080;

    // Cube transformation properties
    glm::vec3 m_CubePosition = glm::vec3(0.0f);
    glm::vec3 m_CubeScale = glm::vec3(1.0f);
    glm::vec3 m_CubeRotation = glm::vec3(0.0f); // Rotation in degrees for X, Y, Z

    // Lighting properties
    glm::vec3 m_LightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 m_LightColor = glm::vec3(1.0f); // White light
    float m_LightIntensity = 1.0f;

    // Camera properties
    glm::vec3 m_CameraPosition;
};
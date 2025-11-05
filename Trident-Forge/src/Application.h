#pragma once

#include <Core.h>

#include "ApplicationLayer.h"

class Application
{
public:
    Application();
    ~Application();

    static Application& Get() { return *s_Instance; };
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
    std::shared_ptr<Engine::EditorCamera> m_EditorCamera;

    std::unique_ptr<Engine::PhysicsSystem> m_PhysicsSystem; // Drives scene integration before rendering.

    std::unique_ptr<Engine::ImGuiLayer> m_ImGuiLayer;
    std::unique_ptr<ApplicationLayer> m_AppLayer;

    int m_Width = 1920;
    int m_Height = 1080;
};
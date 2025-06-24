#include "Application.h"
#include <GLFW/glfw3.h>

#include "Renderer/OpenGL/OpenGLRenderPass.h"
#include "Renderer/RenderCommand.h"

#include "ApplicationLayer.h"

Application* Application::s_Instance = nullptr;

Application::Application() { Init(); }

Application::~Application() { Shutdown(); }

void Application::Run()
{
    while (!glfwWindowShouldClose(m_Window->GetWindow()))
    {
        Engine::Time::Update();
        m_EditorCamera->OnUpdate(Engine::Time::GetDeltaTime());
        glfwPollEvents();

        m_SceneFramebuffer->Bind();
        Engine::RenderCommand::SetClearColor(m_SceneFramebuffer->GetSpecification().ClearColor);
        Engine::RenderCommand::Clear();

        Engine::Renderer::BeginScene(m_RenderPass);

        RenderScene();

        Engine::Renderer::EndScene();
        m_SceneFramebuffer->Unbind();

        glfwSwapBuffers(m_Window->GetWindow());

        m_ImGuiLayer->Begin();

        m_AppLayer->RenderUI();

        m_ImGuiLayer->End();
    }
}

void Application::Init()
{
    s_Instance = this;

    Engine::Time::Init();

    m_Window = std::make_shared<Engine::WindowsWindow>();
    m_Window->Init();

    m_Renderer = std::make_shared<Engine::Renderer>();
    m_Renderer->Init();

    Engine::FramebufferSpecification fbSpec;
    fbSpec.Width = m_Window->GetWidth();
    fbSpec.Height = m_Window->GetHeight();
    fbSpec.ClearColor = { 0.05f, 0.05f, 0.05f, 1.0f };
    m_SceneFramebuffer = Engine::Framebuffer::Create(fbSpec);

    Engine::RenderPassSpecification renderPassSpec;
    renderPassSpec.ClearColor = fbSpec.ClearColor;
    renderPassSpec.TargetFramebuffer = m_SceneFramebuffer;
    m_RenderPass = std::make_shared<Engine::OpenGLRenderPass>(renderPassSpec);

    float aspect = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
    m_EditorCamera = std::make_shared<Engine::EditorCamera>(45.0f, aspect, 0.1f, 100.0f);
    m_EditorCamera->SetViewportSize((float)m_Window->GetWidth(), (float)m_Window->GetHeight());

    glfwSetWindowUserPointer(m_Window->GetWindow(), this);
    glfwSetCursorPosCallback(m_Window->GetWindow(),
        [](GLFWwindow* window, double x, double y)
        {
            Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
            if (app && app->m_EditorCamera)
                app->m_EditorCamera->OnMouseMove(static_cast<float>(x), static_cast<float>(y));
        });
    glfwSetScrollCallback(m_Window->GetWindow(),
        [](GLFWwindow* window, double xoff, double yoff)
        {
            Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
            if (app && app->m_EditorCamera)
                app->m_EditorCamera->OnMouseScroll(static_cast<float>(yoff));
        });
    glfwSetMouseButtonCallback(m_Window->GetWindow(),
        [](GLFWwindow* window, int button, int action, int mods)
        {
            Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
            if (app && app->m_EditorCamera)
                app->m_EditorCamera->OnMouseButton(button, action);
        });

    m_ImGuiLayer = std::make_unique<Engine::ImGuiLayer>();
    m_ImGuiLayer->Init(m_Window->GetWindow());

    m_AppLayer = std::make_unique<ApplicationLayer>(m_SceneFramebuffer, m_EditorCamera, m_Window, m_Width, m_Height);
    m_AppLayer->Init();
}

void Application::RenderScene() { m_AppLayer->RenderScene(); }

void Application::OnEvent(Engine::Event& e) { m_AppLayer->OnEvent(e); }

void Application::RenderUI() { m_AppLayer->RenderUI(); }

void Application::Shutdown()
{
    m_ImGuiLayer->Shutdown();
    m_Window->Shutdown();

    s_Instance = nullptr;
}
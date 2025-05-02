#include "Application.h"
#include <GLFW/glfw3.h>
#include "Renderer/RenderCommand.h"
#include "Renderer/OpenGL/OpenGLRenderPass.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
    Init();
}

Application::~Application()
{
    Shutdown();
}

Application& Application::Get()
{
    return *s_Instance;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_Window->GetWindow()))
    {
        Engine::Time::Update();
        m_CameraController->OnUpdate(Engine::Time::GetDeltaTime());

        m_SceneFramebuffer->Bind();
        Engine::RenderCommand::SetClearColor(m_SceneFramebuffer->GetSpecification().ClearColor);
        Engine::RenderCommand::Clear();

        Engine::Renderer::BeginScene(m_RenderPass);
        RenderScene();
        Engine::Renderer::EndScene();
        m_SceneFramebuffer->Unbind();

        m_ImGuiLayer->Begin();

        RenderUI();

        m_ImGuiLayer->End();

        glfwPollEvents();
        glfwSwapBuffers(m_Window->GetWindow());
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
    fbSpec.ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
    m_SceneFramebuffer = Engine::Framebuffer::Create(fbSpec);

    Engine::RenderPassSpecification renderPassSpec;
    renderPassSpec.ClearColor = fbSpec.ClearColor;
    renderPassSpec.TargetFramebuffer = m_SceneFramebuffer;
    m_RenderPass = std::make_shared<Engine::OpenGLRenderPass>(renderPassSpec);

    float aspect = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
    m_CameraController = std::make_shared<Engine::CameraController>(aspect);
    m_Camera = std::make_unique<Engine::PerspectiveCamera>(m_CameraController->GetCamera());

    m_ImGuiLayer = std::make_unique<Engine::ImGuiLayer>();
    m_ImGuiLayer->Init(m_Window->GetWindow());

    float vertices[] = {
        // Position         // Color               // Normal
        -0.5f, -0.5f, -0.5f,   1,0,0,1,              0, 0, -1,
         0.5f, -0.5f, -0.5f,   0,1,0,1,              0, 0, -1,
         0.5f,  0.5f, -0.5f,   0,0,1,1,              0, 0, -1,
        -0.5f,  0.5f, -0.5f,   1,1,0,1,              0, 0, -1,

        -0.5f, -0.5f,  0.5f,   1,0,1,1,              0, 0, 1,
         0.5f, -0.5f,  0.5f,   0,1,1,1,              0, 0, 1,
         0.5f,  0.5f,  0.5f,   1,1,1,1,              0, 0, 1,
        -0.5f,  0.5f,  0.5f,   0.5,0.5,0.5,1,        0, 0, 1
    };

    uint32_t indices[] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        4,5,1, 1,0,4,
        7,6,2, 2,3,7,
        4,0,3, 3,7,4,
        5,1,2, 2,6,5
    };

    auto vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
    Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "a_Position" },
        { Engine::ShaderDataType::Float4, "a_Color" },
        { Engine::ShaderDataType::Float3, "a_Normal" }
    };
    vertexBuffer->SetLayout(layout);

    auto indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    m_VertexArray = Engine::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_Shader = Engine::Shader::Create("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");

    m_CubePosition = { 0.0f, 0.0f, 0.0f };
    m_CubeScale = { 1.0f, 1.0f, 1.0f };
    m_CubeRotation = { 0.0f, 0.0f, 0.0f };
    m_LightPosition = { 2.0f, 4.0f, 2.0f };
}

void Application::RenderScene()
{
    m_Shader->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_CubePosition)
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_CubeRotation.x), glm::vec3(1, 0, 0))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_CubeRotation.y), glm::vec3(0, 1, 0))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_CubeRotation.z), glm::vec3(0, 0, 1))
        * glm::scale(glm::mat4(1.0f), m_CubeScale);

    glm::mat4 viewProj = m_Camera->GetViewProjectionMatrix();

    m_Shader->SetUniformMat4("u_Model", model);
    m_Shader->SetUniformMat4("u_ViewProjection", viewProj);

    m_Shader->SetUniformFloat3("u_LightPos", m_LightPosition);
    m_Shader->SetUniformFloat3("u_ViewPos", m_CameraController->GetCamera().GetPosition());

    m_VertexArray->Bind();
    Engine::Renderer::DrawIndexed(m_VertexArray);
}

void Application::OnEvent(Engine::Event& e)
{
    Engine::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Engine::WindowResizeEvent>([this](Engine::WindowResizeEvent& ev)
        {
            m_Width = ev.GetWidth();
            m_Height = ev.GetHeight();

            m_SceneFramebuffer->Resize(m_Width, m_Height);
            m_Camera->RecalculateView();

            return false;
        });

    dispatcher.Dispatch<Engine::MouseScrolledEvent>([this](Engine::MouseScrolledEvent& ev)
        {
            m_CameraController->OnScroll(0.1f);
            m_Camera->RecalculateView();

            return false;
        });
}

void Application::RenderUI()
{
    static bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (!opt_padding)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    }

    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    {
        if (!opt_padding)
            ImGui::PopStyleVar();
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }
    ImGui::End();

    ImGui::Begin("Settings");
    {
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::DragFloat3("Cube Position", &m_CubePosition.x, 0.1f);
        ImGui::DragFloat3("Cube Size", &m_CubeScale.x, 0.1f);
        ImGui::DragFloat3("Cube Rotation", &m_CubeRotation.x, 1.0f);
        ImGui::DragFloat3("Light Position", &m_LightPosition.x, 0.1f);
    }
    ImGui::End();

    ImGui::Begin("Scene Viewport");
    {
        ImTextureID texID = (ImTextureID)(uintptr_t)m_SceneFramebuffer->GetColorAttachmentRendererID();
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImGui::Image(texID, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}

void Application::Shutdown()
{
    m_ImGuiLayer->Shutdown();
    m_Window->Shutdown();

    s_Instance = nullptr;
}
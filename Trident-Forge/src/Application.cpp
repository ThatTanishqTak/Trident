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
        // Update time and camera
        Engine::Time::Update();
        m_CameraController->OnUpdate(Engine::Time::GetDeltaTime());

        // 1) Render scene into offscreen framebuffer
        m_SceneFramebuffer->Bind();
        Engine::RenderCommand::SetClearColor(m_SceneFramebuffer->GetSpecification().ClearColor);
        Engine::RenderCommand::Clear();

        Engine::Renderer::BeginScene(m_RenderPass);
        RenderScene();
        Engine::Renderer::EndScene();
        m_SceneFramebuffer->Unbind();

        // Render UI and viewport
        m_ImGuiLayer->Begin();
        
        RenderUI();
        
        m_ImGuiLayer->End();

        // 3) Present
        glfwPollEvents();
        glfwSwapBuffers(m_Window->GetWindow());
    }
}

void Application::Init()
{
    s_Instance = this;

    // Initialize subsystems
    Engine::Time::Init();

    m_Window = std::make_shared<Engine::WindowsWindow>();
    m_Window->Init();

    m_Renderer = std::make_shared<Engine::Renderer>();
    m_Renderer->Init();

    // Create offscreen framebuffer
    Engine::FramebufferSpecification fbSpec;
    fbSpec.Width = m_Window->GetWidth();
    fbSpec.Height = m_Window->GetHeight();
    fbSpec.ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
    m_SceneFramebuffer = Engine::Framebuffer::Create(fbSpec);

    // Default render pass (for UI overlays)
    Engine::RenderPassSpecification renderPassSpec;
    renderPassSpec.ClearColor = fbSpec.ClearColor;
    renderPassSpec.TargetFramebuffer = m_SceneFramebuffer;
    m_RenderPass = std::make_shared<Engine::OpenGLRenderPass>(renderPassSpec);

    // Camera setup
    float aspect = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
    m_CameraController = std::make_shared<Engine::CameraController>(aspect);
    m_Camera = std::make_unique<Engine::PerspectiveCamera>(m_CameraController->GetCamera());

    // ImGui setup
    m_ImGuiLayer = std::make_unique<Engine::ImGuiLayer>();
    m_ImGuiLayer->Init(m_Window->GetWindow());

    // Mesh, buffers, shader
    float vertices[] = {
        // Positions        // Colors
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.5f, 0.5f, 0.5f, 1.0f,
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
        { Engine::ShaderDataType::Float4, "a_Color" }
    };
    vertexBuffer->SetLayout(layout);

    auto indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    m_VertexArray = Engine::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_Shader = Engine::Shader::Create("Shaders/Basic.vert", "Shaders/Basic.frag");
}

void Application::RenderScene()
{
    m_Shader->Bind();

    // Rotate model
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(r), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 viewProj = m_Camera->GetViewProjectionMatrix();

    m_Shader->SetUniformMat4("u_Model", model);
    m_Shader->SetUniformMat4("u_ViewProjection", viewProj);

    m_VertexArray->Bind();
    Engine::Renderer::DrawIndexed(m_VertexArray);
}

void Application::RenderUI()
{
    static bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are creating a full-screen dockspace window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace Demo", &p_open, window_flags);

    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();

    // === SETTINGS PANEL ===
    ImGui::Begin("Settings");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::DragFloat("Rotation", &r, 1.0f, 0.0f, 360.0f);
    ImGui::End();

    // === SCENE VIEWPORT ===
    ImGui::Begin("Scene Viewport");

    // Ensure the framebuffer texture is valid and draw it
    ImTextureID texID = (ImTextureID)(uintptr_t)m_SceneFramebuffer->GetColorAttachmentRendererID();
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ImGui::Image(texID, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0)); // Flip vertically
    ImGui::End();
}

void Application::Shutdown()
{
    m_ImGuiLayer->Shutdown();
    m_Window->Shutdown();
    s_Instance = nullptr;
}
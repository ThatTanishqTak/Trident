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

        RenderUI();

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

    float vertices[] =
    {
          // Back face (−Z)
         -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
          0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
                                                                
          // Front face (+Z)                                     
         -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
         -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f,   0.0f,  0.0f,  1.0f,
                                                                       
          // Left face (−X)                                             
         -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f,  -1.0f,  0.0f,  0.0f,
                                                                      
          // Right face (+X)                                            
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
                                                                      
          // Bottom face (−Y)                                          
         -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
                                                                       
          // Top face (+Y)                                              
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
         -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f,   0.0f,  1.0f,  0.0f,
    };

    uint32_t indices[] =
    {
         // Back face
         0,  1,  2,  2,  3,  0,

         // Front face
         4,  5,  6,  6,  7,  4,

         // Left face
         8,  9, 10, 10, 11,  8,

         // Right face
         12, 13, 14, 14, 15, 12,

         // Bottom face
         16, 17, 18, 18, 19, 16,

         // Top face
         20, 21, 22, 22, 23, 20
    };

    auto vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
    Engine::BufferLayout layout =
    {
        { Engine::ShaderDataType::Float3, "a_Position" },
        { Engine::ShaderDataType::Float4, "a_Color"    },
        { Engine::ShaderDataType::Float3, "a_Normal"   }
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

    m_CameraPosition = m_Camera->GetPosition();
}

void Application::RenderScene()
{
    m_Shader->Bind();

    glm::mat4 l_Model = glm::translate(glm::mat4(1.0f), m_CubePosition)
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_CubeRotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_CubeRotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_CubeRotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::scale(glm::mat4(1.0f), m_CubeScale);

    glm::mat4 l_ViewProj = m_Camera->GetViewProjectionMatrix();

    m_Shader->SetUniformMat4("u_Model", l_Model);
    m_Shader->SetUniformMat4("u_ViewProjection", l_ViewProj);

    m_Shader->SetUniformFloat3("u_LightPos", m_LightPosition);
    m_Shader->SetUniformFloat3("u_ViewPos", m_CameraPosition);

    Engine::RenderCommand::DrawIndexed(m_VertexArray);
}

void Application::OnEvent(Engine::Event& e)
{
    Engine::EventDispatcher l_Dispatcher(e);
    l_Dispatcher.Dispatch<Engine::WindowResizeEvent>([this](Engine::WindowResizeEvent& ev)
    {
        m_Width = ev.GetWidth();
        m_Height = ev.GetHeight();

        m_SceneFramebuffer->Resize(m_Width, m_Height);
        m_Camera->RecalculateView();

        return false;
    });

    l_Dispatcher.Dispatch<Engine::MouseScrolledEvent>([this](Engine::MouseScrolledEvent& ev)
    {
        m_CameraController->OnScroll(0.5f);
        m_Camera->RecalculateView();

        return false;
    });
}

void Application::RenderUI()
{
    ImGui::Begin("Scene Viewport");
    {
        ImTextureID l_TextureID = (ImTextureID)(uintptr_t)m_SceneFramebuffer->GetColorAttachmentRendererID();
        ImVec2 l_ViewportPanelSize = ImGui::GetContentRegionAvail();
        
        ImGui::Image(l_TextureID, l_ViewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();

    // Menu Bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene", "Ctrl+N"))
            { 
                /* Handle New Scene */ 
            }

            if (ImGui::MenuItem("Open Scene...", "Ctrl+O"))
            { 
                /* Handle Open Scene */ 
            }

            if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
            { 
                /* Handle Save Scene */ 
            }

            if (ImGui::MenuItem("Exit", "Alt+F4"))
            { 
                m_Window->CloseWindow(); 
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z"))
            { 
                /* Handle Undo */ 
            }
            
            if (ImGui::MenuItem("Redo", "Ctrl+Y"))
            { 
                /* Handle Redo */ 
            }
            
            ImGui::Separator();
            
            if (ImGui::MenuItem("Cut", "Ctrl+X"))
            { 
                /* Handle Cut */ 
            }

            if (ImGui::MenuItem("Copy", "Ctrl+C"))
            { 
                /* Handle Copy */
            }

            if (ImGui::MenuItem("Paste", "Ctrl+V"))
            { 
                /* Handle Paste */ 
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Scene", nullptr, true))
            {
                /* Handle Scene */
            }

            if (ImGui::MenuItem("Console", nullptr, true))
            {
                /* Example toggle */
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            { 
                /* Handle About */
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Settings");
    {
        // Performance Info
        ImGui::Text("Performance");
        ImGui::Separator();
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        // Cube Info
        ImGui::Spacing();
        ImGui::Text("Cube Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Position", &m_CubePosition.x, 0.1f);
        ImGui::DragFloat3("Scale", &m_CubeScale.x, 0.1f);
        ImGui::DragFloat3("Rotation", &m_CubeRotation.x, 1.0f);

        // Light Info
        ImGui::Spacing();
        ImGui::Text("Light Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Light Position", &m_LightPosition.x, 0.1f);
        ImGui::ColorEdit3("Light Color", &m_LightColor.x);
        ImGui::DragFloat("Light Intensity", &m_LightIntensity, 0.05f, 0.0f, 10.0f);

        // Camera Info
        ImGui::Spacing();
        ImGui::Text("Camera Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Camera Position", &m_CameraPosition.x, 0.1f);
    }
    ImGui::End();
}

void Application::Shutdown()
{
    m_ImGuiLayer->Shutdown();
    m_Window->Shutdown();

    s_Instance = nullptr;
}
#include "ApplicationLayer.h"

#include "Renderer/RenderCommand.h"

#include "ECS/Scene.h"
#include "ECS/Components.h"

ApplicationLayer::ApplicationLayer(const std::shared_ptr<Engine::Framebuffer>& framebuffer, const std::shared_ptr<Engine::CameraController>& cameraController,
    const std::shared_ptr<Engine::WindowsWindow>& window, int& width, int& height) : 
    m_SceneFramebuffer(framebuffer), m_CameraController(cameraController), m_Window(window), m_Width(width), m_Height(height)
{

}

void ApplicationLayer::Init()
{
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
         0,  1,  2,  2,  3,  0,
         4,  5,  6,  6,  7,  4,
         8,  9, 10, 10, 11,  8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
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

    m_CubeEntity = m_Scene.CreateEntity();
    m_Scene.AddComponent<Engine::TagComponent>(m_CubeEntity, "Cube");
    m_Scene.AddComponent<Engine::TransformComponent>(m_CubeEntity);

    m_CameraPosition = m_CameraController->GetCamera().GetPosition();
}

void ApplicationLayer::OnEvent(Engine::Event& e)
{
    Engine::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Engine::WindowResizeEvent>([this](Engine::WindowResizeEvent& ev)
    {
        m_Width = ev.GetWidth();
        m_Height = ev.GetHeight();

        m_SceneFramebuffer->Resize(m_Width, m_Height);
        
        return false;
    });

    dispatcher.Dispatch<Engine::MouseScrolledEvent>([this](Engine::MouseScrolledEvent&  ev)
    {
        m_CameraController->OnScroll(0.5f);
        
        return false;
    });
}

void ApplicationLayer::RenderScene()
{
    m_CameraPosition = m_CameraController->GetCamera().GetPosition();
    m_Shader->Bind();

    auto& transform = m_Scene.GetComponent<Engine::TransformComponent>(m_CubeEntity);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.Translation)
        * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::scale(glm::mat4(1.0f), transform.Scale);

    glm::mat4 viewProj = m_CameraController->GetCamera().GetViewProjectionMatrix();

    m_Shader->SetUniformMat4("u_Model", model);
    m_Shader->SetUniformMat4("u_ViewProjection", viewProj);

    m_Shader->SetUniformFloat3("u_LightPos", m_LightPosition);
    m_Shader->SetUniformFloat3("u_LightColor", m_LightColor);
    m_Shader->SetUniformFloat("u_LightIntensity", m_LightIntensity);
    m_Shader->SetUniformFloat3("u_ViewPos", m_CameraPosition);

    Engine::RenderCommand::DrawIndexed(m_VertexArray);
}

void ApplicationLayer::RenderUI()
{
    ImGui::Begin("Scene Viewport");
    {
        ImTextureID texID = (ImTextureID)(uintptr_t)m_SceneFramebuffer->GetColorAttachmentRendererID();
        ImVec2 size = ImGui::GetContentRegionAvail();

        ImGui::Image(texID, size, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene", "Ctrl+N"))
            {

            }

            if (ImGui::MenuItem("Open Scene...", "Ctrl+O"))
            {

            }

            if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
            {

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

            }

            if (ImGui::MenuItem("Redo", "Ctrl+Y"))
            {

            }

            ImGui::Separator();

            if (ImGui::MenuItem("Cut", "Ctrl+X"))
            {

            }

            if (ImGui::MenuItem("Copy", "Ctrl+C"))
            {

            }

            if (ImGui::MenuItem("Paste", "Ctrl+V"))
            {

            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Scene", nullptr, true))
            {

            }

            if (ImGui::MenuItem("Console", nullptr, true))
            {

            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Settings");
    {
        ImGui::Text("Performance");
        ImGui::Separator();
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        ImGui::Spacing();
        ImGui::Text("Cube Properties");
        ImGui::Separator();
        auto& transform = m_Scene.GetComponent<Engine::TransformComponent>(m_CubeEntity);
        ImGui::DragFloat3("Position", &transform.Translation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform.Rotation.x, 1.0f);

        ImGui::Spacing();
        ImGui::Text("Light Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Light Position", &m_LightPosition.x, 0.1f);
        ImGui::ColorEdit3("Light Color", &m_LightColor.x);
        ImGui::DragFloat("Light Intensity", &m_LightIntensity, 0.05f, 0.0f, 10.0f);

        ImGui::Spacing();
        ImGui::Text("Camera Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Camera Position", &m_CameraPosition.x, 0.1f);
        m_CameraController->SetCameraPosition(m_CameraPosition);
    }
    ImGui::End();
}
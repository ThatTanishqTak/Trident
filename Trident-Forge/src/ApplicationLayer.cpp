#include "ApplicationLayer.h"

#include "Renderer/Renderer3D.h"

#include "ECS/Scene.h"
#include "ECS/Components.h"

ApplicationLayer::ApplicationLayer(const std::shared_ptr<Engine::Framebuffer>& framebuffer, const std::shared_ptr<Engine::CameraController>& cameraController,
    const std::shared_ptr<Engine::WindowsWindow>& window, int& width, int& height) : 
    m_SceneFramebuffer(framebuffer), m_CameraController(cameraController), m_Window(window), m_Width(width), m_Height(height)
{

}

void ApplicationLayer::Init()
{
    Engine::Renderer3D::Init();

    m_CubeEntity = m_Scene.CreateEntity();
    m_CubeEntity.AddComponent<Engine::TagComponent>("Cube");
    m_CubeEntity.AddComponent<Engine::TransformComponent>();

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

    auto& transform = m_CubeEntity.GetComponent<Engine::TransformComponent>();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.Translation)
        * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::scale(glm::mat4(1.0f), transform.Scale);

    glm::mat4 viewProj = m_CameraController->GetCamera().GetViewProjectionMatrix();
    Engine::Renderer3D::DrawCube(model, viewProj, m_LightPosition, m_LightColor, m_LightIntensity, m_CameraPosition);
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
        auto& transform = m_CubeEntity.GetComponent<Engine::TransformComponent>();
        ImGui::DragFloat3("Position", &transform.Translation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform.Rotation.x, 1.0f);
        //auto& color = m_Scene.GetComponent<Engine::ColorComponent>(m_CubeEntity);
        //ImGui::ColorEdit3("Color", &color.Color.x, 0.1f);
        //ImGui::DragFloat("Alpha", &color.Alpha, 0.1f, 0.0f, 1.0f);

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
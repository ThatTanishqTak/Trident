#include "ApplicationLayer.h"

#include "Renderer/Renderer3D.h"
#include "SceneHierarchyPanel.h"
#include <GLFW/glfw3.h>

ApplicationLayer::ApplicationLayer(const std::shared_ptr<Engine::Framebuffer>& framebuffer, const std::shared_ptr<Engine::EditorCamera>& camera,
    const std::shared_ptr<Engine::WindowsWindow>& window, int& width, int& height) :
    m_SceneFramebuffer(framebuffer), m_Camera(camera), m_Window(window), m_Width(width), m_Height(height)
{

}

void ApplicationLayer::Init()
{
    Engine::Renderer3D::Init();

    m_CameraPosition = m_Camera->GetPosition();
    m_SceneHierarchyPanel.SetContext(&m_Scene);
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

    dispatcher.Dispatch<Engine::MouseScrolledEvent>([this](Engine::MouseScrolledEvent& ev)
    {
        m_Camera->OnMouseScroll(ev.GetYOffset());
        
        return false;
    });
}

void ApplicationLayer::RenderScene()
{
    m_CameraPosition = m_Camera->GetPosition();

    glm::mat4 viewProj = m_Camera->GetViewProjectionMatrix();

    m_Scene.ForEach<Engine::TransformComponent, Engine::PrimitiveComponent>([&](Engine::Entity entity, Engine::TransformComponent& transform, Engine::PrimitiveComponent& primitive)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.Translation)
                * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
                * glm::scale(glm::mat4(1.0f), transform.Scale);
            
            switch (primitive.Type)
            {
            case Engine::PrimitiveType::Cube:
                Engine::Renderer3D::DrawCube(model, viewProj, m_LightPosition, m_LightColor, m_LightIntensity, m_CameraPosition);
                break;
            case Engine::PrimitiveType::Sphere:
                Engine::Renderer3D::DrawSphere(model, viewProj, m_LightPosition, m_LightColor, m_LightIntensity, m_CameraPosition);
                break;
            case Engine::PrimitiveType::Quad:
                Engine::Renderer3D::DrawQuad(model, viewProj, m_LightPosition, m_LightColor, m_LightIntensity, m_CameraPosition);
                break;
            case Engine::PrimitiveType::Plane:
                Engine::Renderer3D::DrawPlane(model, viewProj, m_LightPosition, m_LightColor, m_LightIntensity, m_CameraPosition);
                break;
            }
        });
}

void ApplicationLayer::RenderUI()
{
    ImGui::Begin("Scene Viewport");
    {
        ImTextureID texID = (ImTextureID)(uintptr_t)m_SceneFramebuffer->GetColorAttachmentRendererID();
        ImVec2 size = ImGui::GetContentRegionAvail();

        ImGui::Image(texID, size, ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::BeginPopupContextWindow("SceneContext", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            if (ImGui::BeginMenu("Add"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    double mouseX, mouseY;
                    glfwGetCursorPos(m_Window->GetWindow(), &mouseX, &mouseY);
                    glm::vec3 worldPos = ScreenToWorld(static_cast<float>(mouseX), static_cast<float>(mouseY));
                    m_SelectedEntity = SpawnCube(worldPos);
                }

                if (ImGui::MenuItem("Sphere"))
                {
                    double mouseX, mouseY;
                    glfwGetCursorPos(m_Window->GetWindow(), &mouseX, &mouseY);
                    glm::vec3 worldPos = ScreenToWorld(static_cast<float>(mouseX), static_cast<float>(mouseY));
                    m_SelectedEntity = SpawnSphere(worldPos);
                    m_SceneHierarchyPanel.SetSelectedEntity(m_SelectedEntity);
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }
    }
    ImGui::End();

    m_SceneHierarchyPanel.OnImGuiRender();
    m_SelectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();

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
        ImGui::Text("Light Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Light Position", &m_LightPosition.x, 0.1f);
        ImGui::ColorEdit3("Light Color", &m_LightColor.x);
        ImGui::DragFloat("Light Intensity", &m_LightIntensity, 0.05f, 0.0f, 10.0f);

        ImGui::Spacing();
        ImGui::Text("Camera Properties");
        ImGui::Separator();
        ImGui::DragFloat3("Camera Position", &m_CameraPosition.x, 0.1f);
        m_Camera->SetPosition(m_CameraPosition);
    }
    ImGui::End();

    ImGui::Begin("Properties");
    {
        if (m_SelectedEntity)
        {
            ImGui::Text("Entity Properties");
            ImGui::Separator();
            auto& transform = m_SelectedEntity.GetComponent<Engine::TransformComponent>();
            ImGui::DragFloat3("Position", &transform.Translation.x, 0.1f);
            ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
            ImGui::DragFloat3("Rotation", &transform.Rotation.x, 1.0f);
        }
    }
    ImGui::End();
}

Engine::Entity ApplicationLayer::SpawnCube(const glm::vec3& position)
{
    Engine::Entity entity = m_Scene.CreateEntity();
    entity.AddComponent<Engine::TagComponent>("Cube");
    auto& tc = entity.AddComponent<Engine::TransformComponent>();
    tc.Translation = position;
    entity.AddComponent<Engine::PrimitiveComponent>(Engine::PrimitiveType::Cube);
    entity.AddComponent<Engine::ColorComponent>();

    return entity;
}

Engine::Entity ApplicationLayer::SpawnSphere(const glm::vec3& position)
{
    Engine::Entity entity = m_Scene.CreateEntity();
    entity.AddComponent<Engine::TagComponent>("Sphere");
    auto& tc = entity.AddComponent<Engine::TransformComponent>();
    tc.Translation = position;
    auto& pc = entity.AddComponent<Engine::PrimitiveComponent>();
    pc.Type = Engine::PrimitiveType::Sphere;
    entity.AddComponent<Engine::ColorComponent>();

    return entity;
}

glm::vec3 ApplicationLayer::ScreenToWorld(float mouseX, float mouseY) const
{
    glm::vec4 viewport{ 0.0f, 0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height) };
    glm::vec3 screenPos{ mouseX, static_cast<float>(m_Height) - mouseY, 0.0f };
    glm::mat4 view = m_Camera->GetViewMatrix();
    glm::mat4 proj = m_Camera->GetProjectionMatrix();
    glm::vec3 world = glm::unProject(screenPos, view, proj, viewport);

    return world;
}
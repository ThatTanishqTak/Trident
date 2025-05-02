#pragma once

#include <memory>

#include "WindowsWindow/WindowsWindow.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderPass.h"
#include "Renderer/OpenGL/OpenGLRenderPass.h"

#include "Camera/CameraController.h"
#include "Camera/PerspectiveCamera.h"
#include "Camera/EditorCamera.h"

#include "ImGui/ImGuiLayer.h"

#include "Utilities/Time.h"

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
	std::unique_ptr<Engine::EditorCamera> m_EditorCamera;

	std::unique_ptr<Engine::ImGuiLayer> m_ImGuiLayer;

	int m_Width = 1920;
	int m_Height = 1080;

private:
	// Cube transformation properties
	glm::vec3 m_CubePosition = glm::vec3(0.0f);
	glm::vec3 m_CubeScale = glm::vec3(1.0f);
	glm::vec3 m_CubeRotation = glm::vec3(0.0f); // Rotation in degrees for X, Y, Z

	// Lighting
	glm::vec3 m_LightPosition = glm::vec3(2.0f, 4.0f, 2.0f);
};
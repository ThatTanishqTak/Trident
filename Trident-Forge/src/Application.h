#pragma once

#include <memory>

#include "WindowsWindow/WindowsWindow.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderPass.h"
#include "Renderer/OpenGL/OpenGLRenderPass.h"

#include "Camera/CameraController.h"
#include "Camera/PerspectiveCamera.h"

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

private:
	static Application* s_Instance;

	std::shared_ptr<Engine::WindowsWindow> m_Window;
	std::shared_ptr<Engine::Renderer> m_Renderer;
	std::shared_ptr<Engine::RenderPass> m_RenderPass;

	std::shared_ptr<Engine::CameraController> m_CameraController;
	std::unique_ptr<Engine::PerspectiveCamera> m_Camera;
	std::unique_ptr<Engine::ImGuiLayer> m_ImGuiLayer;

	std::shared_ptr<Engine::VertexArray> m_VertexArray;
	std::shared_ptr<Engine::Shader> m_Shader;
};
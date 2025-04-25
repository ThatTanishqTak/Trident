#pragma once

#include "Core.h"
#include "Utilities/Time.h"

#include "WindowsWindow/WindowsWindow.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

#include "Camera/CameraController.h"

#include "ImGui/ImGuiLayer.h"

#include <memory>

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	std::shared_ptr<Engine::WindowsWindow> m_Window;

	std::shared_ptr<Engine::Renderer> m_Renderer;
	std::shared_ptr<Engine::VertexArray> m_VertexArray;
	std::shared_ptr<Engine::Shader> m_Shader;

	std::unique_ptr<Engine::Camera> m_Camera;
	std::shared_ptr<Engine::CameraController> m_CameraController;

	std::unique_ptr<Engine::ImGuiLayer> m_ImGuiLayer;

private:
	void Init();
	void Shutdown();

	void RenderUI();
};
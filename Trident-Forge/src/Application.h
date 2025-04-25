#pragma once

#include "Core.h"
#include "WindowsWindow/WindowsWindow.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

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

	void Init();
	void Shutdown();

	void RenderUI();
};
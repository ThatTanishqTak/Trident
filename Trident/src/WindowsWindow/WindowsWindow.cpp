#include "WindowsWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	void WindowsWindow::Init()
	{
		m_WindowAPI = WindowAPI::Create();
		m_WindowAPI->Init();
	}

	void WindowsWindow::Shutdown()
	{

	}

	GLFWwindow* WindowsWindow::GetWindow() const
	{
		return static_cast<GLFWwindow*>(m_WindowAPI->GetNativeWindow());
	}
}
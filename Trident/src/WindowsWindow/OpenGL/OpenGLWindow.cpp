#include "OpenGLWindow.h"
#include <iostream>

namespace Engine
{
	OpenGLWindow::~OpenGLWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		
		std::cout << "Window cleanup successful" << std::endl;
	}

	void OpenGLWindow::Init()
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW!" << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(1920, 1080, "Trident-Forge", nullptr, nullptr);
		if (!m_Window)
		{
			std::cerr << "Failed to create GLFW window!" << std::endl;
			glfwTerminate();
			
			return;
		}
		std::cout << "Window initialization successful" << std::endl;

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD!" << std::endl;
			
			return;
		}
		std::cout << "GLAD initialization successful" << std::endl;

		glfwSwapInterval(1);
		std::cout << "V-Sync enabled" << std::endl;
	}

	void* OpenGLWindow::GetNativeWindow() const
	{
		return m_Window;
	}
}
#pragma once

#include "WindowsWindow/WindowAPI.h"

#include <functional>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{
	class OpenGLWindow : public WindowAPI
	{
	public:
		~OpenGLWindow();

		void Init() override;
		void* GetNativeWindow() const override;

	private:
		GLFWwindow* m_Window = nullptr;

		static void GLFWErrorCallback(int error, const char* description);
	};
}
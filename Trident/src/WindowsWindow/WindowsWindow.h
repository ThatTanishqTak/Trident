#pragma once

#include "WindowAPI.h"
#include <memory>

struct GLFWwindow;

namespace Engine
{
	class WindowsWindow
	{
	public:
		void Init();
		void Shutdown();

		// Returns GLFWwindow* as the native window
		GLFWwindow* GetWindow() const;

	private:
		std::unique_ptr<WindowAPI> m_WindowAPI;
	};
}
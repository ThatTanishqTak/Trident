#pragma once

#include <memory>

namespace Engine
{
	enum class WindowAPIType
	{
		None = 0,
		OpenGL
	};

	class WindowAPI
	{
	public:
		virtual ~WindowAPI() = default;

		virtual void Init() = 0;

		// Native pointer to window (GLFWwindow* for OpenGL)
		virtual void* GetNativeWindow() const = 0;

		static WindowAPIType GetAPI();
		static std::unique_ptr<WindowAPI> Create();
	};
}
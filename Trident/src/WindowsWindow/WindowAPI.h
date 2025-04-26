#pragma once

#include <memory>
#include <functional>

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
		virtual void* GetNativeWindow() const = 0; // Native pointer to window (GLFWwindow* for OpenGL)

		static WindowAPIType GetAPI();
		static std::unique_ptr<WindowAPI> Create();
	};
}
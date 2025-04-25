#pragma once

#include "WindowAPI.h"
#include <memory>
#include "Events/Event.h"

struct GLFWwindow;

//using EventCallbackFn = std::function<void(Event&)>;

namespace Engine
{
	class WindowsWindow
	{
	public:
		void Init();
		void Shutdown();

		// Returns GLFWwindow* as the native window
		GLFWwindow* GetWindow() const;

		//void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
		//EventCallbackFn& GetEventCallback() { return m_EventCallback; }

	private:
		std::unique_ptr<WindowAPI> m_WindowAPI;
		//EventCallbackFn m_EventCallback;
	};
}
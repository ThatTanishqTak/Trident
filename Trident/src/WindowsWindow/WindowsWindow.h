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

        int GetWidth() { return m_WindowAPI->GetWidth(); }
        int GetHeight() { return m_WindowAPI->GetHeight(); }

        void CloseWindow() { m_WindowAPI->CloseWindow(); }

        // Returns GLFWwindow* as the native window
        GLFWwindow* GetWindow() const;

    private:
        std::unique_ptr<WindowAPI> m_WindowAPI;
    };
}
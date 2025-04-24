#pragma once

#include "Core.h"

namespace Engine
{
    // Manages a GLFW window
    class WindowsWindow
    {
    public:
        GLFWwindow* GetWindow() { return m_Window; } // Getter for internal window pointer

        void Init();     // Initializes the GLFW window
        void Shutdown(); // Cleans up GLFW resources

    private:
        GLFWwindow* m_Window = nullptr; // Pointer to the actual GLFW window
    };
}
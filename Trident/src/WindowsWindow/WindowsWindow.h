#pragma once

#include "Core/Core.h"
#include <GLFW/glfw3.h>

namespace Engine
{
    // Manages a GLFW window
    class WindowsWindow
    {
    public:
        GLFWwindow* GetWindow() const { return m_Window; } // Accessor for internal window pointer

        void Init();     // Initializes the GLFW window
        void Shutdown(); // Cleans up GLFW resources

        void Run();      // Renders and updates the window

    private:
        GLFWwindow* m_Window = nullptr; // Pointer to the actual GLFW window
    };
}
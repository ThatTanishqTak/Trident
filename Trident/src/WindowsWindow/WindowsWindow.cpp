#include "WindowsWindow.h"

namespace Engine
{
    void WindowsWindow::Init()
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW!" << std::endl;

            return;
        }

        // Set OpenGL version (Optional: Only needed if you're using modern OpenGL)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // For macOS uncomment the next line
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // Create a windowed mode window and its OpenGL context
        m_Window = glfwCreateWindow(1920, 1080, "Forge", nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();

            return;
        }

        // Make the window's context current
        glfwMakeContextCurrent(m_Window);

        // Load OpenGL functions with GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD!" << std::endl;
            
            return;
        }

        // Enable V-Sync
        glfwSwapInterval(1);
    }

    void WindowsWindow::Shutdown()
    {
        // Cleanup
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}
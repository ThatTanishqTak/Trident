#include "WindowsWindow.h"

namespace Engine
{
    void WindowsWindow::Init()
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW!" << std::endl;

            //return -1;
        }

        // Set OpenGL version (Optional: Only needed if you're using modern OpenGL)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

            //return -1;
        }

        // Make the window's context current
        glfwMakeContextCurrent(m_Window);

        // Enable V-Sync
        glfwSwapInterval(1);
    }

    void WindowsWindow::Shutdown()
    {
        // Cleanup
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void WindowsWindow::Run()
    {
        // Set background color and clear
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Poll for and process events
        glfwPollEvents();

        // Swap front and back buffers
        glfwSwapBuffers(m_Window);
    }
}
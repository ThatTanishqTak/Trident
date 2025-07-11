#include "OpenGLWindow.h"

#include <iostream>

namespace Engine
{
    OpenGLWindow::~OpenGLWindow()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void OpenGLWindow::Init()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW!" << std::endl;

            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Width, m_Height, "Trident-Forge", nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();

            return;
        }

        glfwMakeContextCurrent(m_Window);

        glfwSetErrorCallback(GLFWErrorCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD!" << std::endl;

            return;
        }

        glfwSwapInterval(1);
    }

    void* OpenGLWindow::GetNativeWindow() const { return m_Window; }

    int OpenGLWindow::GetWidth() const { return m_Width; }

    int OpenGLWindow::GetHeight() const { return m_Height; }

    void OpenGLWindow::CloseWindow() const { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

    void OpenGLWindow::GLFWErrorCallback(int error, const char* description)
    {
        std::cerr << "[GLFW Error] (" << error << "): " << description << std::endl;
    }
}
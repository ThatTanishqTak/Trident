#include "Application.h"

Application::Application()
{
    Init(); // Initialize the application
}

Application::~Application()
{
    Shutdown(); // Clean up resources
}

void Application::Run()
{
    // Main loop runs while the window is open
    while (!glfwWindowShouldClose(m_Window.GetWindow()))
    {
        m_Window.Run(); // Render and process events
    }
}

void Application::Init()
{
    m_Window.Init(); // Initialize the window
}

void Application::Shutdown()
{
    m_Window.Shutdown(); // Clean up the window
}
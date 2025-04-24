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
        // Set background color and clear
        m_Renderer.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        m_Renderer.Clear();

        // Render scene
        //m_Renderer.Render();

        // Render userinterface
        RenderUI();

        // Poll for and process events
        glfwPollEvents();

        // Swap front and back buffers
        glfwSwapBuffers(m_Window.GetWindow());
    }
}

void Application::Init()
{
    m_Window.Init(); // Initialize the window
    m_Renderer.Init(); // Initialize the renderer
}

void Application::Shutdown()
{
    //m_Renderer.Shutdown(); // Clean up the renderer
    m_Window.Shutdown(); // Clean up the window
}

void Application::RenderUI()
{
    // Here goes ImGui code
}
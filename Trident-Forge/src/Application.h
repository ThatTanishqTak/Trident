#pragma once

#include "Core.h"
#include "WindowsWindow/WindowsWindow.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

#include <iostream>
#include <memory>

// Represents the core application
class Application
{
public:
    Application();  // Constructor initializes the application
    ~Application(); // Destructor handles cleanup

    void Run();     // Starts the application loop

private:
    Engine::WindowsWindow m_Window; // The main application window
    //Engine::Renderer m_Renderer;    // The Renderer

    std::shared_ptr<Engine::Renderer> m_Renderer;

    // NEW: Rendering resources
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Shader> m_Shader;

private:
    void Init();     // Initializes resources and systems
    void Shutdown(); // Cleans up resources and systems

    void RenderUI(); // Renders UI using ImGui
};
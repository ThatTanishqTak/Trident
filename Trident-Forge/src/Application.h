#pragma once

#include "Core/Core.h"
#include "WindowsWindow/WindowsWindow.h"
#include "Renderer/Renderer.h"

#include <iostream>

// Represents the core application
class Application
{
public:
    Application();  // Constructor initializes the application
    ~Application(); // Destructor handles cleanup

    void Run();     // Starts the application loop

private:
    Engine::WindowsWindow m_Window; // The main application window
    Engine::Renderer m_Renderer; // The main application window

    void Init();     // Initializes resources and systems
    void Shutdown(); // Cleans up resources and systems
};
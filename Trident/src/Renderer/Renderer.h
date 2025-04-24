#pragma once

#include "Core.h"

#include "Shader.h"

namespace Engine
{
    // Renderer handles all OpenGL rendering operations for the engine
    class TRIDENT_API Renderer
    {
    public:
        Renderer();     // Constructor: initializes member variables
        ~Renderer();    // Destructor: cleans up resources

        void Init();    // Initialize buffers, shaders, etc.
        void Render();  // Render the scene (triangle)
        void Shutdown();// Clean up GPU resources

    private:
        GLuint m_VAO;   // Vertex Array Object: stores vertex attribute state
        GLuint m_VBO;   // Vertex Buffer Object: stores vertex data

        class Shader* m_Shader; // Pointer to the Shader used for rendering
    };
}
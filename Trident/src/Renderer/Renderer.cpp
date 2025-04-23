#include "Renderer.h"
#include "Shader.h"

#include <glad/glad.h>
#include <iostream>

namespace Engine
{
    Renderer::Renderer() : m_VAO(0), m_VBO(0), m_Shader(nullptr)
    {
        // Initialize all member variables to default/null values
    }

    Renderer::~Renderer()
    {
        // Clean-up is handled in Shutdown()
    }

    void Renderer::Init()
    {
        // Vertex positions for a simple triangle
        float vertices[] =
        {
             0.0f,  0.5f, 0.0f, // Top vertex
            -0.5f, -0.5f, 0.0f, // Bottom left vertex
             0.5f, -0.5f, 0.0f  // Bottom right vertex
        };

        // Generate and bind Vertex Array Object (VAO)
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        std::cout << "VAO generated and binded successfully" << std::endl;

        // Generate and bind Vertex Buffer Object (VBO)
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        std::cout << "VBO generated and binded successfully" << std::endl;

        // Define layout of vertex data for shader (position attribute)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        std::cout << "Vertex attribute pointers generated successful" << std::endl;

        // Create and compile shaders
        m_Shader = new Shader("Shaders/Basic.vert", "Shaders/Basic.frag");
        std::cout << "Shaders loaded successfully" << std::endl;

        // Unbind the buffer and VAO to avoid accidental modification
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Renderer::Render()
    {
        // Activate the shader program
        m_Shader->Bind();

        // Bind the VAO and draw the triangle
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Unbind the shader program
        m_Shader->Unbind();
    }

    void Renderer::Shutdown()
    {
        // Delete shader
        delete m_Shader;
        m_Shader = nullptr;

        // Delete VAO and VBO
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        std::cout << "Renderer clean up successful" << std::endl;
    }
}
#include "Renderer.h"
#include "Shader.h"

#include <glad/glad.h>
#include <iostream>

namespace Engine
{
    Renderer::Renderer() : m_VAO(0), m_VBO(0), m_Shader(nullptr)
    {

    }

    Renderer::~Renderer()
    {

    }

    void Renderer::Init()
    {
        // Vertex data for a triangle
        float vertices[] =
        {
             0.0f,  0.5f, 0.0f, // Top
            -0.5f, -0.5f, 0.0f, // Bottom Left
             0.5f, -0.5f, 0.0f  // Bottom Right
        };

        // Generate and bind VAO
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        std::cout << "VAO generated and binded successfully" << std::endl;

        // Generate and bind VBO
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        std::cout << "VBO generated and binded successfully" << std::endl;

        // Vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        std::cout << "Vertex attribute pointers generated successfully" << std::endl;

        // Load and compile shaders
        m_Shader = new Shader("Shaders/Basic.vert", "Shaders/Basic.frag");
        std::cout << "Shaders loaded successfully" << std::endl;

        // Unbind everything
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Renderer::Render()
    {
        m_Shader->Bind();
        
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        m_Shader->Unbind();
    }

    void Renderer::Shutdown()
    {
        delete m_Shader;
        m_Shader = nullptr;

        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        std::cout << "Renderer clean up successfull" << std::endl;
    }
}
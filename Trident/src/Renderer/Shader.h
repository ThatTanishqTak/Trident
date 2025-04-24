#pragma once

#include "Core.h"

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Engine
{
    // Shader class encapsulates shader program creation, compilation, and usage
    class TRIDENT_API Shader
    {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath); // Load, compile, and link shaders
        ~Shader(); // Cleanup

        void Bind() const; // Activate shader
        void Unbind() const; // Deactivate shader

        GLuint GetID() const { return m_RendererID; } // Access raw OpenGL program ID

    private:
        GLuint m_RendererID; // OpenGL shader program ID

        std::string LoadShaderSource(const std::string& filepath); // Reads shader code from file
        GLuint CompileShader(GLenum type, const std::string& source); // Compiles individual shader
        GLuint CreateShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc); // Links shaders into a program
    };
}
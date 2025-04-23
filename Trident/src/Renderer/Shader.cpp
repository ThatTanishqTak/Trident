#include "Shader.h"
#include "Utilities/FileUtils.h"

#include <glad/glad.h>
#include <iostream>

namespace Engine
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        // Load shader source code from files
        std::string vertexCode = LoadShaderSource(vertexPath);
        std::string fragmentCode = LoadShaderSource(fragmentPath);

        // Compile and link shaders into a program
        m_RendererID = CreateShaderProgram(vertexCode, fragmentCode);
    }

    Shader::~Shader()
    {
        // Delete the shader program from GPU
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID); // Use this shader program
    }

    void Shader::Unbind() const
    {
        glUseProgram(0); // Stop using any shader program
    }

    std::string Shader::LoadShaderSource(const std::string& filepath)
    {
        // Read the shader source code from file
        std::string code = FileUtils::ReadFile(filepath);
        if (code.empty())
        {
            std::cerr << "Shader file is empty or failed to load: " << filepath << std::endl;
        }
        
        return code;
    }

    GLuint Shader::CompileShader(GLenum type, const std::string& source)
    {
        GLuint shader = glCreateShader(type);          // Create shader object (vertex or fragment)
        const char* src = source.c_str();

        glShaderSource(shader, 1, &src, nullptr);      // Set the shader source code
        glCompileShader(shader);                       // Compile the shader

        // Check for compilation errors
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            
            std::cerr << "Shader Compilation Error: " << infoLog << std::endl;
        }

        return shader;
    }

    GLuint Shader::CreateShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);       // Attach vertex shader
        glAttachShader(program, fragmentShader);     // Attach fragment shader
        glLinkProgram(program);                      // Link shaders into a single program

        // Check for linking errors
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(program, 1024, nullptr, infoLog);
            
            std::cerr << "Shader Linking Error: " << infoLog << std::endl;
        }

        // Shaders are linked, we can delete the intermediates now
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }
}
#include "Shader.h"
#include "Utilities/FileUtils.h"

#include <glad/glad.h>
#include <iostream>

namespace Engine
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexCode = LoadShaderSource(vertexPath);
        std::string fragmentCode = LoadShaderSource(fragmentPath);
        m_RendererID = CreateShaderProgram(vertexCode, fragmentCode);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    std::string Shader::LoadShaderSource(const std::string& filepath)
    {
        std::string code = FileUtils::ReadFile(filepath);
        if (code.empty())
            std::cerr << "Shader file is empty or failed to load: " << filepath << std::endl;
        return code;
    }

    GLuint Shader::CompileShader(GLenum type, const std::string& source)
    {
        GLuint shader = glCreateShader(type);
        const char* src = source.c_str();

        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        // Error checking
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
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        // Error checking
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(program, 1024, nullptr, infoLog);
            std::cerr << "Shader Linking Error: " << infoLog << std::endl;
        }

        // Clean up
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }
}
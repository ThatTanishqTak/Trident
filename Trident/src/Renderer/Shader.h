#pragma once

#include <string>
#include <unordered_map>
//#include <glm/glm.hpp> // If needed later for uniforms

namespace Engine
{
    class Shader
    {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        GLuint GetID() const { return m_RendererID; }

    private:
        GLuint m_RendererID;

        std::string LoadShaderSource(const std::string& filepath);
        GLuint CompileShader(GLenum type, const std::string& source);
        GLuint CreateShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}
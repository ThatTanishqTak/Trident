#include "Renderer/Shader.h"
#include "OpenGL/OpenGLShader.h"

#include "Renderer/RendererAPI.h"

namespace Engine
{
    std::shared_ptr<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:
            {
                return nullptr;
            }

            case RendererAPI::API::OpenGL:
            {
                return std::make_shared<OpenGLShader>(vertexPath, fragmentPath);
            }
        }

        return nullptr;
    }
}
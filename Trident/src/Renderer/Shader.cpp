#include "Renderer/Shader.h"
#include "Renderer/RendererAPI.h"
#include "OpenGL/OpenGLShader.h"

namespace Engine
{
	std::shared_ptr<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
			{
				return nullptr;
			}

			case RendererAPIType::OpenGL:
			{
				std::cout << "Creating Shader: " << vertexPath << ", " << fragmentPath << std::endl;
				return std::make_shared<OpenGLShader>(vertexPath, fragmentPath);
			}
		}

		return nullptr;
	}
}
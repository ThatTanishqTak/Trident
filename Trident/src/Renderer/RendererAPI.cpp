#include "RendererAPI.h"
#include "OpenGL/OpenGLRenderer.h"

namespace Engine
{
	static RendererAPIType s_API = RendererAPIType::OpenGL;

	RendererAPIType RendererAPI::GetAPI()
	{
		return s_API;
	}

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPIType::OpenGL:
			{
				return std::make_unique<OpenGLRenderer>();
			}

			case RendererAPIType::None:
			default:
			{
				return nullptr;
			}
		}
	}
}
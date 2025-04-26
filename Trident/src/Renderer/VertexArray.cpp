#include "Renderer/VertexArray.h"
#include "Renderer/RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
			{
				return nullptr;
			}

			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLVertexArray>();
			}
		}

		return nullptr;
	}
}
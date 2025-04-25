#include "Renderer/VertexArray.h"
#include "Renderer/RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
			{
				return nullptr;
			}

			case RendererAPIType::OpenGL:
			{
				return std::make_shared<OpenGLVertexArray>();
			}
		}

		return nullptr;
	}
}
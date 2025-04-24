#include "Renderer/VertexArray.h"
#include "Renderer/RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
			{
				return nullptr;
			}

			case RendererAPIType::OpenGL:
			{
				return new OpenGLVertexArray();
			}
		}

		return nullptr;
	}
}
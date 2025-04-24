#include "VertexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "Renderer/RendererAPI.h"

namespace Engine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
			{
				return nullptr;
			}

			case RendererAPIType::OpenGL:
			{
				return new OpenGLVertexBuffer(vertices, size);
			}
		}

		return nullptr;
	}
}
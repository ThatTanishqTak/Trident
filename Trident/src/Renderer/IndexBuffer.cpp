#include "IndexBuffer.h"
#include "Renderer/RendererAPI.h"
#include "OpenGL/OpenGLIndexBuffer.h"

namespace Engine
{
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
			{
				return nullptr;
			}

			case RendererAPI::API::OpenGL:
			{ 
				return std::make_shared<OpenGLIndexBuffer>(indices, count);
			}
		}

		return nullptr;
	}
}
#include "VertexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"

#include "Renderer/RendererAPI.h"

namespace Engine
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:
            {
                return nullptr;
            }

            case RendererAPI::API::OpenGL:
            {
                return std::make_shared<OpenGLVertexBuffer>(vertices, size);
            }
        }

        return nullptr;
    }
}
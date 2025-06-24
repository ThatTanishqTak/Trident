#include "Renderer/Framebuffer.h"
#include "OpenGL/OpenGLFramebuffer.h"

#include "Renderer/RendererAPI.h"

namespace Engine
{
    std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:
            {
                return nullptr;
            }

            case RendererAPI::API::OpenGL:
            {
                return std::make_shared<OpenGLFramebuffer>(spec);
            }
        }

        return nullptr;
    }
}
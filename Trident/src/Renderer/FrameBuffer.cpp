#include "Renderer/Framebuffer.h"
#include "Renderer/RendererAPI.h"
#include "OpenGL/OpenGLFramebuffer.h"

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
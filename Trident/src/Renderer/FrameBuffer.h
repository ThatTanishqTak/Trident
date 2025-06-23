#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
    struct FramebufferSpecification
    {
        uint32_t Width = 1920;
        uint32_t Height = 1080;
        glm::vec4 ClearColor;
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual uint32_t GetColorAttachmentRendererID() const = 0;

        const FramebufferSpecification& GetSpecification() const { return m_Specification; }
        static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);

    protected:
        FramebufferSpecification m_Specification;
    };
}
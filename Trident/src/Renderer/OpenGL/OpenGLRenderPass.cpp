#include "OpenGLRenderPass.h"
#include "Renderer/RenderCommand.h"

namespace Engine
{
    OpenGLRenderPass::OpenGLRenderPass(const RenderPassSpecification& spec) { m_Specification = spec; }

    void OpenGLRenderPass::Begin()
    {
        if (m_Specification.TargetFramebuffer)
        {
            m_Specification.TargetFramebuffer->Bind();
        }

        else
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0); // Default
        }

        RenderCommand::SetClearColor(m_Specification.ClearColor);
        RenderCommand::Clear();
    }

    void OpenGLRenderPass::End()
    {
        if (m_Specification.TargetFramebuffer)
        {
            m_Specification.TargetFramebuffer->Unbind();
        }
    }
}
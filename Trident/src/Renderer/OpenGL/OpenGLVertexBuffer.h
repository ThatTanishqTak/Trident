#pragma once

#include "Renderer/VertexBuffer.h"

namespace Engine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        const BufferLayout& GetLayout() const override { return m_Layout; }

    private:
        uint32_t m_RendererID;
    };

}
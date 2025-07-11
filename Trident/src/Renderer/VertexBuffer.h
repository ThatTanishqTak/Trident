#pragma once

#include "Renderer/BufferLayout.h"

#include <iostream>
#include <memory>

namespace Engine
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);

    protected:
        BufferLayout m_Layout;
    };
}
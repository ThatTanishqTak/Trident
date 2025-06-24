#pragma once

#include <glm/glm.hpp>

namespace Engine
{
    class RenderCommand
    {
    public:
        static void Init();
        static void SetClearColor(const glm::vec4& color);
        static void Clear();
        static void DrawIndexed(const std::shared_ptr<class VertexArray>& vertexArray);
    };
}
#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace Engine
{
    class VertexArray;

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
            // Vulkan, DirectX could be added later
        };

    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };
}
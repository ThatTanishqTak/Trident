#pragma once

#include "Renderer/VertexArray.h"

#include <memory>

namespace Engine
{
    class Geometry
    {
    public:
        static const std::shared_ptr<VertexArray>& GetCube();
        static const std::shared_ptr<VertexArray>& GetSphere();
        static const std::shared_ptr<VertexArray>& GetQuad();
        static const std::shared_ptr<VertexArray>& GetPlane();

        static void Shutdown();
    };
}
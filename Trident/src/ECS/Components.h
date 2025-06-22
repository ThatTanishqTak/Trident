#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Engine
{
    struct TagComponent
    {
        std::string Tag;
    };

    struct TransformComponent
    {
        glm::vec3 Translation{ 0.0f };
        glm::vec3 Rotation{ 0.0f };
        glm::vec3 Scale{ 1.0f };
    };

    struct ColorComponent
    {
        glm::vec3 Color{ 1.0f };
        float Alpha{ 1.0f };
    };
}
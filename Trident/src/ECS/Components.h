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

    enum class PrimitiveType
    {
        Cube = 0,
        Sphere,
        Quad,
        Plane
    };

    struct PrimitiveComponent
    {
        PrimitiveType Type{ PrimitiveType::Cube };
    };

    struct LightComponent
    {
        glm::vec3 Color{ 1.0f };
        float Intensity{ 1.0f };
    };

    struct SpriteComponent
    {
        glm::vec4 Color{ 1.0f };
    };
}
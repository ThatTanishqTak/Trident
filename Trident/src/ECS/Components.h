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

    enum class LightType
    {
        Directional = 0,
        Point,
        Spot,
        Area
    };

    struct LightComponent
    {
        LightType Type{ LightType::Point };
        glm::vec3 Color{ 1.0f };
        float Intensity{ 1.0f };
        glm::vec3 Direction{ 0.0f, -1.0f, 0.0f };
        float CutOff{ 12.5f };
        float OuterCutOff{ 17.5f };
    };

    struct SpriteComponent
    {
        glm::vec4 Color{ 1.0f };
    };
}
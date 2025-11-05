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

    // A lightweight physics component that stores the mass properties required by
    // Engine::PhysicsSystem. The values follow the naming convention requested by
    // the tooling team so that future contributors immediately know which scope
    // owns the data. Additional state (forces, torque, collision volumes, etc.) can
    // be bolted on here later without breaking the API surface.
    struct RigidBodyComponent
    {
        float m_Mass{ 1.0f };                 // Kilogram mass used to scale applied accelerations.
        glm::vec3 m_Velocity{ 0.0f };         // Linear velocity integrated every frame.
        glm::vec3 m_Acceleration{ 0.0f };     // Accumulated acceleration (e.g., gravity or forces).
        float m_Damping{ 0.0f };              // Linear damping factor in the [0, 1] range.
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
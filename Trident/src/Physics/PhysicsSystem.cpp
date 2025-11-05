#include "PhysicsSystem.h"

#include <algorithm>
#include <glm/glm.hpp>

namespace Engine
{
    PhysicsSystem::PhysicsSystem(Scene& scene) : m_Scene(scene)
    {

    }

    void PhysicsSystem::Step(float deltaTime)
    {
        // Guard against negative time steps that could destabilize the solver.
        const float l_ClampedDeltaTime = std::max(deltaTime, 0.0f);
        if (l_ClampedDeltaTime <= 0.0f)
        {
            return;
        }

        m_Scene.ForEach<TransformComponent, RigidBodyComponent>(
            [l_ClampedDeltaTime](Entity entity, TransformComponent& transform, RigidBodyComponent& rigidbody)
            {
                (void)entity; // Unused for now but reserved for future per-entity overrides.

                if (rigidbody.m_Mass <= 0.0f)
                {
                    return;
                }

                // Semi-implicit (symplectic) Euler:
                // v_{t+dt} = (v_t + a_t * dt) * damping
                // x_{t+dt} = x_t + v_{t+dt} * dt
                const glm::vec3 l_AccelerationStep = rigidbody.m_Acceleration * l_ClampedDeltaTime;
                glm::vec3 l_Velocity = rigidbody.m_Velocity + l_AccelerationStep;

                const float l_DampedFactor = glm::clamp(1.0f - (rigidbody.m_Damping * l_ClampedDeltaTime), 0.0f, 1.0f);
                l_Velocity *= l_DampedFactor;

                const glm::vec3 l_PositionStep = l_Velocity * l_ClampedDeltaTime;
                transform.Translation += l_PositionStep;

                rigidbody.m_Velocity = l_Velocity;

                // TODO: Apply collision impulses and constraints before committing the final pose.
            });

        // TODO: Broad-phase and narrow-phase collision detection can be slotted here once shapes exist.
    }
}
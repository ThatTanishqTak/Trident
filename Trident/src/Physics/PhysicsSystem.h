#pragma once

#include "ECS/Scene.h"
#include "ECS/Components.h"

namespace Engine
{
    // PhysicsSystem drives rigid body integration for entities that expose both a
    // TransformComponent and a RigidBodyComponent. The goal is to keep the system
    // simple today while providing clear seams for future upgrades such as
    // collision detection, constraint solvers, and force accumulation buffers.
    class PhysicsSystem
    {
    public:
        explicit PhysicsSystem(Scene& scene);

        // Integrate velocities and positions using a semi-implicit (symplectic)
        // Euler step. Velocity is updated first and the new value is then used to
        // advance the translation, which keeps the simulation stable for simple
        // rigid body motion.
        void Step(float deltaTime);

    private:
        Scene& m_Scene;
    };
}
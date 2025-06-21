#pragma once

#include "Registry.h"
#include <utility>

namespace Engine
{
    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        template<typename T, typename... Args>
        T& AddComponent(Entity entity, Args&&... args)
        {
            return m_Registry.AddComponent<T>(entity, std::forward<Args>(args)...);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            m_Registry.RemoveComponent<T>(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return m_Registry.GetComponent<T>(entity);
        }

        template<typename T>
        bool HasComponent(Entity entity) const
        {
            return m_Registry.HasComponent<T>(entity);
        }

        template<typename... Ts, typename Func>
        void ForEach(Func func)
        {
            m_Registry.ForEach<Ts...>(std::move(func));
        }

    private:
        Registry m_Registry;
    };
}

#include "Scene.inl"
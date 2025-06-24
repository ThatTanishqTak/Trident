#pragma once

#include "Entity.h"

#include <entt/entt.hpp>

namespace Engine
{
    class Registry
    {
    public:
        entt::entity CreateEntity();
        void DestroyEntity(entt::entity entity);

        template <typename T, typename... Args> T& AddComponent(entt::entity entity, Args &&...args);

        template <typename T> void RemoveComponent(entt::entity entity);

        template <typename T> T& GetComponent(entt::entity entity);

        template <typename T> const T& GetComponent(entt::entity entity) const;

        template <typename T> bool HasComponent(entt::entity entity) const;

        template <typename... Ts, typename Func> void ForEach(Func func);

        template <typename... Ts, typename Func> void ForEach(Func func) const;

    private:
        entt::registry m_Registry;
    };
}

// ------------------ Implementation ------------------

namespace Engine
{
    inline entt::entity Registry::CreateEntity() { return m_Registry.create(); }

    inline void Registry::DestroyEntity(entt::entity entity) { m_Registry.destroy(entity); }

    template <typename T, typename... Args> T& Registry::AddComponent(entt::entity entity, Args &&...args)
    {
        return m_Registry.emplace<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T> void Registry::RemoveComponent(entt::entity entity) { m_Registry.remove<T>(entity); }

    template <typename T> T& Registry::GetComponent(entt::entity entity) { return m_Registry.get<T>(entity); }

    template <typename T> const T& Registry::GetComponent(entt::entity entity) const { return m_Registry.get<T>(entity); }

    template <typename T> bool Registry::HasComponent(entt::entity entity) const { return m_Registry.all_of<T>(entity); }

    template <typename... Ts, typename Func> void Registry::ForEach(Func func)
    {
        auto view = m_Registry.view<Ts...>();
        for (auto entity : view)
        {
            func(entity, view.get<Ts>(entity)...);
        }
    }

    template <typename... Ts, typename Func> void Registry::ForEach(Func func) const
    {
        auto view = m_Registry.view<Ts...>();
        for (auto entity : view)
        {
            func(entity, view.get<Ts>(entity)...);
        }
    }
}
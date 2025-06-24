#pragma once

#include <entt/entt.hpp>

namespace Engine
{
    class Scene;

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene) : m_Entity(handle), m_Scene(scene) {}

        bool IsValid() const { return m_Entity != entt::null && m_Scene; }

        operator bool() const { return IsValid(); }
        operator entt::entity() const { return m_Entity; }

        template <typename T, typename... Args> T& AddComponent(Args &&...args);

        template <typename T> void RemoveComponent();

        template <typename T> T& GetComponent();

        template <typename T> const T& GetComponent() const;

        template <typename T> bool HasComponent() const;

        entt::entity GetHandle() const { return m_Entity; }

        bool operator==(const Entity& other) const;
        bool operator!=(const Entity& other) const;

    private:
        entt::entity m_Entity{ entt::null };
        Scene* m_Scene{ nullptr };
    };

    constexpr Entity kInvalidEntity{};
}

#include "Scene.h"

namespace Engine
{
    template <typename T, typename... Args> T& Entity::AddComponent(Args &&...args)
    {
        return m_Scene->AddComponent<T>(*this, std::forward<Args>(args)...);
    }

    template <typename T> void Entity::RemoveComponent() { m_Scene->RemoveComponent<T>(*this); }

    template <typename T> T& Entity::GetComponent() { return m_Scene->GetComponent<T>(*this); }

    template <typename T> const T& Entity::GetComponent() const { return m_Scene->GetComponent<T>(*this); }

    template <typename T> bool Entity::HasComponent() const { return m_Scene->HasComponent<T>(*this); }

    inline bool Entity::operator==(const Entity& other) const { return m_Entity == other.m_Entity && m_Scene == other.m_Scene; }
    inline bool Entity::operator!=(const Entity& other) const { return !(*this == other); }
}
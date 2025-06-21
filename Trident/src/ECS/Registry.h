#pragma once

#include "Entity.h"

#include <entt/entt.hpp>

namespace Engine
{
	class Registry
	{
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		template<typename T, typename... Args>
		T& AddComponent(Entity entity, Args&&... args);

		template<typename T>
		void RemoveComponent(Entity entity);

		template<typename T>
		T& GetComponent(Entity entity);

		template<typename T>
		bool HasComponent(Entity entity) const;

		template<typename... Ts, typename Func>
		void ForEach(Func func);

	private:
		entt::registry m_Registry;
	};
}

// ------------------ Implementation ------------------
namespace Engine
{
	inline Entity Registry::CreateEntity()
	{
		return m_Registry.create();
	}

	inline void Registry::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	template<typename T, typename... Args>
	T& Registry::AddComponent(Entity entity, Args&&... args)
	{
		return m_Registry.emplace<T>(entity, std::forward<Args>(args)...);
	}

	template<typename T>
	void Registry::RemoveComponent(Entity entity)
	{
		m_Registry.remove<T>(entity);
	}

	template<typename T>
	T& Registry::GetComponent(Entity entity)
	{
		return m_Registry.get<T>(entity);
	}

	template<typename T>
	bool Registry::HasComponent(Entity entity) const
	{
		return m_Registry.all_of<T>(entity);
	}

	template<typename... Ts, typename Func>
	void Registry::ForEach(Func func)
	{
		auto view = m_Registry.view<Ts...>();
		for (auto entity : view)
			func(entity, view.get<Ts>(entity)...);
	}
}
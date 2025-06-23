namespace Engine
{
    inline Entity Scene::CreateEntity()
    {
        auto handle = m_Registry.CreateEntity();
        return Entity(handle, this);
    }

    inline void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.DestroyEntity(entity);
    }
}
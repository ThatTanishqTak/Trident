namespace Engine
{
    inline Entity Scene::CreateEntity()
    {
        return m_Registry.CreateEntity();
    }

    inline void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.DestroyEntity(entity);
    }
}
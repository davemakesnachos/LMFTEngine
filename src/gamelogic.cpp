#include <memory>

#include <entityfactory.h>
#include <gamelogic.h>

int GameLogic::init(void)
{
    m_entityFactory = new EntityFactory;
    if (m_entityFactory == nullptr) {
        ERROR("Failed to create EntityFactory!")
        return -ERR_ENOMEM;
    }

    return 0;
}

std::weak_ptr<Entity> GameLogic::getEntity(const unsigned int id)
{
    auto entityIt = m_entityMap.find(id);
    if (entityIt != m_entityMap.end())
        return entityIt->second;
    return std::weak_ptr<Entity>();
}

std::shared_ptr<Entity> GameLogic::createEntity(json data, const char *name )
{
    std::shared_ptr<Entity> entity = m_entityFactory->createEntity(data, name);
    if (entity)
    {
        m_entityMap.insert(std::make_pair(entity->getId(), entity));
        /* TODO: Report this event */
        return entity;
    }
    else
    {
        ERROR("Failed to create entity " << name);
        return std::shared_ptr<Entity>();
    }
}

std::shared_ptr<Entity> GameLogic::createEntity(const char *entityResource)
{
    json data;

    /* TODO: Populate data once we can parse resources */

    return createEntity(data, entityResource);
}

void GameLogic::destroyEntity(const unsigned int id)
{
    /* TODO: Emit SYNCHRONOUS event before we delete */

    auto entityIt = m_entityMap.find(id);
    if (entityIt != m_entityMap.end())
    {
        entityIt->second->destroy();
        m_entityMap.erase(entityIt);
    }
}

int GameLogic::onUpdate(double dt)
{
    return 0;
}

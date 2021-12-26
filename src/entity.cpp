#include <nlohmann/json.hpp>
#include <utility>

#include <component.h>
#include <entity.h>
#include <logger.h>

using json = nlohmann::json;

Entity::Entity(unsigned long id) { m_id = id; }
Entity::~Entity(void) { }

int Entity::init(json data)
{
    m_type = data.at("type");
    DEBUG("Init entity type " << m_type << " with id " << getId());
    return 0;
}

void Entity::postInit(void)
{
    for (auto it = m_components.begin(); it != m_components.end(); ++it)
    {
        it->second->postInit();
    }
}

void Entity::update(double dt)
{
    for (auto it = m_components.begin(); it != m_components.end(); ++it)
    {
        it->second->update(dt);
    }
}

void Entity::destroy(void)
{
    m_components.clear();
}

unsigned long Entity::getId(void)
{
    return m_id;
}

template <class ComponentType>
std::weak_ptr<ComponentType> Entity::getComponent(unsigned long id)
{
    auto findIt = m_components.find(id);
    if (findIt != m_components.end())
    {
        std::shared_ptr<EntityComponent> baseComponent(findIt->second);
        std::shared_ptr<ComponentType> subComponent(std::static_pointer_cast<ComponentType>(baseComponent));
        std::weak_ptr<ComponentType> subComponentWeakPtr(subComponent);
        return subComponentWeakPtr;
    }
    else
    {
        return std::weak_ptr<ComponentType>();
    }
}

void Entity::addComponent(std::shared_ptr<EntityComponent> component)
{
    std::pair<EntityComponents::iterator, bool> success = m_components.insert(std::make_pair(component->getComponentId(), component));
}

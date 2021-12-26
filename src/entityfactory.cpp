#include <nlohmann/json.hpp>

#include <entityfactory.h>
#include <componentfactory.h>
#include <logger.h>

#include <component/transform2d_component.h>

using json = nlohmann::json;

EntityFactory::EntityFactory(void)
{
    m_lastEntityId = INVALID_ENTITY_ID;

    _componentFactory.registerComponent<Transform2dComponent>(Transform2dComponent::getComponentIdFromName(Transform2dComponent::_name));
}

std::shared_ptr<Entity> EntityFactory::createEntity(const char *entityResource)
{
    ERROR("Resource based createEntity not yet implemented.");
    return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity> EntityFactory::createEntity(json data, const char *name)
{
    unsigned int nextEntityId = INVALID_ENTITY_ID;
	if (nextEntityId == INVALID_ENTITY_ID)
	{
		nextEntityId = getNextEntityId();
	}

    std::shared_ptr<Entity> entity(new Entity(nextEntityId));
    if (entity->init(data))
    {
        ERROR("Failed to initialize entity: " << std::string(name));
        return std::shared_ptr<Entity>();
    }

    json componentData;

    try
    {
        componentData = data.at("components");
    }
    catch (json::out_of_range& e)
    {
        ERROR("Missing \"components\" entry for entity " << std::string(name));
    }

    for (json::iterator it = componentData.begin(); it != componentData.end(); ++it) {
        std::shared_ptr<EntityComponent> component(createComponent(*it));
        if (component)
        {
            entity->addComponent(component);
            component->setOwner(entity);
        }
        else
        {
            // Return empty entity, we have failed
            return std::shared_ptr<Entity>();
        }
    }

    // All components created, so run post init
    entity->postInit();

    return entity;
}

std::shared_ptr<EntityComponent> EntityFactory::createComponent(json data)
{
    std::string name = data["name"];
    std::shared_ptr<EntityComponent> component(_componentFactory.create(EntityComponent::getComponentIdFromName(name.c_str())));

    // initialize the component if we found one
    if (component)
    {
        if (component->init(data))
        {
            ERROR("Component failed to initialize: " << std::string(name));
            return std::shared_ptr<EntityComponent>();
        }
    }
    else
    {
        ERROR("Couldn't find EntityComponent named " << std::string(name));
        return std::shared_ptr<EntityComponent>();  // fail
    }

    // pComponent will be NULL if the component wasn't found.  This isn't necessarily an error since you might have a 
    // custom CreateComponent() function in a sub class.
    return component;
}

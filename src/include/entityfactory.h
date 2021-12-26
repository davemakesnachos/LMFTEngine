#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include <componentfactory.h>
#include <entity.h>

class EntityFactory {
protected:
    EntityComponentFactory _componentFactory;

public:
    EntityFactory(void);

    std::shared_ptr<Entity> createEntity(json data, const char *name = "");
    std::shared_ptr<Entity> createEntity(const char *entityResource);

    virtual std::shared_ptr<EntityComponent> createComponent(json data);

private:
    unsigned int m_lastEntityId;

    unsigned int getNextEntityId(void) { ++m_lastEntityId; return m_lastEntityId; }
};
#endif /* _ENTITYFACTORY_H_ */
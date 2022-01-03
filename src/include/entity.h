#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class EntityComponent;

typedef std::map<unsigned long, std::shared_ptr<EntityComponent> > EntityComponents;

#define INVALID_ENTITY_ID 0

class Entity {

    friend class EntityFactory;

public:
    explicit Entity(unsigned long id);
    ~Entity(void);

    int init(json data);
    void postInit(void);
    void update(double dt);
    void destroy(void);

    unsigned long getId(void);

    template <class ComponentType>
    std::weak_ptr<ComponentType> getComponent(unsigned long id);

private:
    void addComponent(std::shared_ptr<EntityComponent> component);

    unsigned long m_id;
    EntityComponents m_components;
    std::string m_type;
};

#endif /* _ENTITY_H_ */
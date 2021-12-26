#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <functional>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Entity;

class EntityComponent {

    friend class EntityFactory;

    protected:
        std::shared_ptr<Entity> m_owner;

    public:
        virtual int init(json data) = 0;
        virtual void postInit(void) { };
        virtual void update(double dt) { };

        virtual const char *getComponentName() const = 0;
        unsigned long getComponentId(void) const { return getComponentIdFromName(getComponentName()); };

        static unsigned int getComponentIdFromName(const char *name) {
            return std::hash<std::string>{}(name);
        }

    private:
        void setOwner(std::shared_ptr<Entity> owner) { m_owner = owner; }
};

#endif /* _COMPONENT_H_ */
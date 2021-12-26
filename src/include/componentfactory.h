#ifndef _COMPONENTFACTORY_H_
#define _COMPONENTFACTORY_H_

#include <map>

#include <component.h>
#include <error.h>
#include <logger.h>

template <class SubType>
EntityComponent* CreateEntityComponentFunc(void) { return new SubType; }

class EntityComponentFactory
{
    typedef EntityComponent* (*CreateEntityComponentFuncType)(void);
    std::map<unsigned int, CreateEntityComponentFuncType> m_creatorFunctions;

public:
    template <class SubClass>
    int registerComponent(unsigned int id) {
        auto findIt = m_creatorFunctions.find(id);
        if (findIt == m_creatorFunctions.end())
        {
            m_creatorFunctions[id] = &CreateEntityComponentFunc<SubClass>;
            DEBUG("Registering Component " << SubClass::_name << " id: " << id);
            return 0;
        }
        ERROR("Failed to register Component " << SubClass::_name << " id: " << id);
        return -ERR_ENOENT;
    }

    EntityComponent* create(unsigned int id) {
        DEBUG("Attempting to create component with id " << id);
        auto findIt = m_creatorFunctions.find(id);
        if (findIt != m_creatorFunctions.end())
        {
            CreateEntityComponentFuncType pFunc = findIt->second;
            return pFunc();
        }

        return NULL;
    }
};

#endif /* _COMPONENTFACTORY_H_ */
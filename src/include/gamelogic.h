#ifndef _GAMELOGIC_
#define _GAMELOGIC_

#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

#include <types.h>

using json = nlohmann::json;

class Entity;
class EntityFactory;

class GameLogic
{
public:
    virtual std::weak_ptr<Entity> getEntity(const unsigned int id);
    virtual std::shared_ptr<Entity> createEntity(json data, const char *name = "");
    virtual std::shared_ptr<Entity> createEntity(const char *entityResource);
    virtual void destroyEntity(const unsigned int id);

    virtual int init(void);
    virtual int onUpdate(double dt);
    virtual int onSystemEvent(SystemEventType *e) = 0;

    virtual std::string getGameName(void) = 0;
private:
    std::map<unsigned int, std::shared_ptr<Entity> > m_entityMap;

    EntityFactory *m_entityFactory;
};

std::shared_ptr<GameLogic> createGameLogic(void);

#endif /* _GAMELOGIC_ */

#include <gamelogic.h>

int GameLogic::init(void)
{
    return 0;
}

std::weak_ptr<Entity> GameLogic::getEntity(const unsigned int id)
{
    return std::weak_ptr<Entity>();
}

std::shared_ptr<Entity> GameLogic::createEntity(json data, const char *name )
{
    return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity> GameLogic::createEntity(const char *entityResource)
{
    return std::shared_ptr<Entity>();
}

void GameLogic::destroyEntity(const unsigned int id)
{
}

int GameLogic::onUpdate(double dt)
{
    return 0;
}

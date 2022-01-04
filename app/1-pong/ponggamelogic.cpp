#include <gamelogic.h>

#include <logger.h>
#include <physicssystem.h>

#include <physics/physicsbox2d.h>

#include "ponggamelogic.h"

PongGameLogic::PongGameLogic(void)
{
    PhysicsSystemData physData;

    physData.gravityX = 0;
    physData.gravityY = -1.0;

    m_physicsSystem = createPhysicsSystem();
    m_physicsSystem->init(physData);
}

std::string PongGameLogic::getGameName(void)
{
    return "Pong";
}

int PongGameLogic::onSystemEvent(SystemEventType *e)
{
    return 0;
}

std::shared_ptr<GameLogic> createGameLogic(void)
{
    return std::shared_ptr<PongGameLogic>(new PongGameLogic);
}
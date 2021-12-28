#include <gamelogic.h>

#include <logger.h>

#include "ponggamelogic.h"

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
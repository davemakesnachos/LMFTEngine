#include <gamelogic.h>

class PongGameLogic : public GameLogic
{
    int onSystemEvent(SystemEventType *e);
    virtual std::string getGameName(void);
};
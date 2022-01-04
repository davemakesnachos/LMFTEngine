#include <gamelogic.h>

class PongGameLogic : public GameLogic
{
public:
    PongGameLogic(void);
    int onSystemEvent(SystemEventType *e);
    virtual std::string getGameName(void);
};
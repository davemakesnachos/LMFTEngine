#ifndef GAME_H
#define GAME_H

#include <memory>

class GameLogic;
class Window;

class Game
{
public:
	Game(void);
	int init(void);
	int run(void);
	void destroy(void);

	int getWidth();
	int getHeight();

	std::shared_ptr<GameLogic> _gameLogic;

private:
	double updateTicks();

	bool m_running;
	int m_lastTicks;

	int m_gameHeight, m_gameWidth;

	Window *m_window;
};
#endif /* GAME_H */
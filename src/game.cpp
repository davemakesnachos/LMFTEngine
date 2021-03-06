#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <error.h>
#include <eventmanager.h>
#include <game.h>
#include <gamelogic.h>
#include <logger.h>
#include <timer.h>
#include <types.h>
#include <window.h>

Game *g_game = NULL;

Game::Game(void)
{
	m_running = true;
    m_lastTicks = 0;

    g_game = this;
}

int Game::init(void)
{
    int ret;

    Logger::init();
	INFO("Init Game");

    m_gameWidth = 800;
    m_gameHeight = 600;

	m_eventManager = EventManager::create();
	if (m_eventManager == nullptr) {
		ERROR("Cannot init event handler!");
		return -ERR_ENOMEM;
	}

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        ERROR("SDL_Init Error: " << SDL_GetError());
        return -1;
    }

    m_window = new Window(this);

    m_window->init();

    m_gameLogic = createGameLogic();
    if (m_gameLogic) {
        if(ret = m_gameLogic->init()) {
            ERROR("Failure to init game logic. Code: " << ret);
        }
    } else {
        ERROR("Failure to create game logic.");
    }

    INFO("Created base game logic for " << m_gameLogic->getGameName());

    return ret;
}

void Game::destroy(void)
{
	/* How do we destory m_gameLogic? */
	INFO("Destroying Game");

	m_window->destroy();

	SDL_Quit();
}

int Game::run(void)
{
    SDL_Renderer *r;
    int ret = 0;
    double dt;

    /* TODO: Handle Error code! */
    init();

    r = m_window->getRenderer();

    while(m_running)
    {
        SystemEventType e;

        dt = updateTicks();

        while (SDL_PollEvent(&e))
        {
            ret = m_gameLogic->onSystemEvent(&e);

            if (ret == ERR_OVERRIDDEN)
                continue;

            switch(e.type)
            {
                case SDL_QUIT:
                    m_running = false;
                    break;
            }
        }

        m_gameLogic->onUpdate(dt);
        m_eventManager->onUpdate(10);

        SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
        SDL_RenderClear(r);

        SDL_RenderPresent(r);
    }

    destroy();

	INFO("Exiting with return code " << ret);

    return ret;
}

int Game::getWidth()
{
    return m_gameWidth;
}

int Game::getHeight()
{
    return m_gameHeight;
}

double Game::updateTicks(void)
{
    double dt = (Timer::timestamp() - m_lastTicks) / 1000.0;
    m_lastTicks = Timer::timestamp();

    return dt;
}

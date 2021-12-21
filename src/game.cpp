#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <game.h>
#include <logger.h>
#include <window.h>

Game::Game(void)
{
	m_running = true;
    m_lastTicks = 0;
}

int Game::init(void)
{
    Logger::init();

    m_gameWidth = 800;
    m_gameHeight = 600;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        ERROR("SDL_Init Error: " << SDL_GetError());
        return -1;
    }

    m_window = new Window(this);

    m_window->init();

    return 0;
}

void Game::destroy(void)
{
	m_window->destroy();

	SDL_Quit();
}

int Game::run(void)
{
    SDL_Renderer *r;
    int ret = 0;
    double dt;

    init();

    r = m_window->getRenderer();

    while(m_running)
    {
        SDL_Event e;

        dt = updateTicks();

        while (SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    m_running = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
        SDL_RenderClear(r);

        SDL_RenderPresent(r);
    }

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
    double dt = (SDL_GetTicks() - m_lastTicks) / 1000.0;
    m_lastTicks = SDL_GetTicks();

    return dt;
}

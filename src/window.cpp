#include <SDL.h>
#include <stdio.h>

#include <window.h>
#include <logger.h>

int Window::init(void)
{
    int ret = 0;

    m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_game->getWidth(), m_game->getHeight(), SDL_WINDOW_SHOWN );

    if (m_window == nullptr )
    {
        ERROR("Window could not be created! SDL_Error: " << SDL_GetError() );
    }

    DEBUG("Created window " << m_game->getWidth() << " x " << m_game->getHeight());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        ERROR("SDL_CreateRenderer Error: " << SDL_GetError());
        SDL_DestroyWindow(m_window);
        return false;
    }

    SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);

    SDL_RenderSetLogicalSize(getRenderer(), m_game->getWidth(), m_game->getHeight());

    return ret;
}

void Window::destroy(void)
{
	SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
}

SDL_Window* Window::getWindow() {
    return m_window;
}

SDL_Renderer* Window::getRenderer() {
    return m_renderer;
}

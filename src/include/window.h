#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#include <game.h>

class Window {

public:
    Window(Game *g) { m_game = g; };

    int init(void);
    void destroy(void);
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

private:
    Game *m_game;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};

#endif /* WINDOW_H */
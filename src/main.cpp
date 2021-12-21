#include <SDL.h>
#include <stdio.h>

#include <game.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main( int argc, char* args[] )
{
    Game game;
    return game.run();
}
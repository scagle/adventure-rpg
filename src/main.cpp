#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include "gamedata.hpp"

int main(int argc, char *argv[])
{
    /*! TODO: Fix this annoying static problem
     *  \todo Fix this annoying static problem
     */
    game::GameData gamedata = game::GameData(); // Initialize Game Sessions
    gamedata.start(); // Start Game
    gamedata.updateMap(0);

    SDL_Event event;
    while ( !gamedata.isDone() )
    {
        gamedata.checkInputs(&event);
        gamedata.update();
        gamedata.render();
    }
    return 0;
} 

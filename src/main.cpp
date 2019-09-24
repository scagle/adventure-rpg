#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include "gamedata.hpp"

int main(int argc, char *argv[])
{
    game::GameData gamedata = game::GameData(); // Initialize Game Session
    gamedata.updateMap(0);

    SDL_Event event;
    while ( !gamedata.isDone() )
    {
        gamedata.checkInputs(&event);
        gamedata.update();
        gamedata.render();
    }

    gamedata.close();
    return 0;
} 

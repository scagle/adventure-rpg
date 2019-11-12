#include "gamedata.hpp"

#include <chrono>
#include <thread>
#include <SDL.h>

void render_thread(game::GameData *gamedata) 
{
    while ( !gamedata->isDone() )
    {
        auto begin = std::chrono::steady_clock::now();
        gamedata->render();
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast< std::chrono::milliseconds >( end - begin );
        std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) - duration );
    }
}

int main(int argc, char *argv[])
{
    /*! TODO: Fix this annoying static problem
     *  \todo Fix this annoying static problem
     */
    game::GameData gamedata = game::GameData(); // Initialize Game Sessions
    gamedata.startGame(); 
    std::thread rt( render_thread, &gamedata );

    SDL_Event event;
    while ( !gamedata.isDone() )
    {
        auto begin = std::chrono::steady_clock::now();
        gamedata.checkInputs( &event );
        gamedata.update();
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast< std::chrono::milliseconds >( end - begin );
        std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) - duration );
    }
    rt.join();

    return 0;
}


#include <iostream>
#include <assert.h>
#include "gamedata.hpp"
#include "sdl_utils.hpp"

namespace game
{
    GameData::GameData()
    {
        keyboard_handler = KeyboardHandler();
        menu_handler = MenuHandler();
        main_character = Character( SDL_Rect{0, 0, 20, 20}, SDL_Color{255, 50, 50} );
        world = World();

        if ( this->init() )
            std::cout << "Success!" << "\n";
        else
            std::cout << "Failure!" << "\n";
    }

    void GameData::checkInputs( SDL_Event* event )
    {
        if (initialized != true)
            return;

        while ( SDL_PollEvent( event ) != 0 )
        {
            if ( event->type == SDL_QUIT )
            {
                quit = true;   
            }
            else if ( event->type == SDL_KEYDOWN )
            {
                switch ( event->key.keysym.sym )
                {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_ESCAPE:
                        if (menu_handler.inMenu())
                            menu_handler.popMenu();
                        else
                            menu_handler.pushMenu("main");
                        break;
                    case SDLK_j:
                        if (menu_handler.inMenu())
                            menu_handler.moveMenu(MenuHandler::DOWN);
                        break;
                    case SDLK_k:
                        if (menu_handler.inMenu())
                            menu_handler.moveMenu(MenuHandler::UP);
                        break;
                    case SDLK_RETURN:
                        if (menu_handler.inMenu())
                            menu_handler.selectMenu();
                        break;
                    default: 
                        break;
                }
            }
            keyboard_handler.handleEvent(event);
        }
    }

    void GameData::update()
    {
        // Update Character
        float velocity_x = keyboard_handler.getHorizontal() * MAIN_CHARACTER_SPEED;
        float velocity_y = keyboard_handler.getVertical()   * MAIN_CHARACTER_SPEED;
        main_character.setVelocity(velocity_x, velocity_y);
        main_character.update(&statics);
    }

    void GameData::render()
    {
        // Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear( renderer );

        // Draw Characters
        main_character.render( renderer );

        // Draw Solid Objects
        for ( Solid solid : statics )
            solid.render( renderer );

        // Draw Menu
        menu_handler.render( renderer );

        //Update screen
        SDL_RenderPresent( renderer );
    }

    void GameData::updateMap(int map_index)
    {
        map_index = map_index;
        statics = world.getMap(map_index)->getSolids();
    }

    bool GameData::init()
    {
        // SDL
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL couldn't be initialized! : %s\n", SDL_GetError() ); 
            return false;
        }

        // SDL_Window
        window = SDL_CreateWindow ( 
                "Game", 
                SDL_WINDOWPOS_UNDEFINED, 
                SDL_WINDOWPOS_UNDEFINED, 
                SCREEN_WIDTH, 
                SCREEN_HEIGHT, 
                0 
        );
        if ( window == NULL )
        {
            printf( "Window couldn't be created! : %s\n", SDL_GetError() );
            return false;
        }

        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if ( renderer == NULL )
        {
            printf( "Renderer couldn't be created! : %s\n", SDL_GetError() );
            return false;
        }

        // Maps
        if ( !world.loadMaps() )
        {
            printf( "Maps couldn't be initialized! \n"); 
            return false;
        }
            
        // Surface
        surface = SDL_GetWindowSurface( window );

        initialized = true;
        return true;
    }


    bool GameData::close()
    {
        bool success = true; // proof by contradiction
        // Deallocate the surface
        SDL_FreeSurface( surface );
        surface = NULL;

        // Destroy window
        SDL_DestroyWindow( window );
        SDL_DestroyRenderer( renderer );
        window = NULL;
        renderer = NULL;

        SDL_Quit();

        printf("Goodbye!\n");

        return success;
    }
}

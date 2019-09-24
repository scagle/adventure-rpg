#include <iostream>
#include <assert.h>
#include "gamedata.hpp"
#include "utils/sdl_utils.hpp"

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
    // Draw Background
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );

    // Draw Characters
    SDL_FillRect( surface, main_character.getRekt(), main_character.getColorNumber() );

    // Draw Solid Objects
    if (statics.size() != 0)
    {
        for (unsigned int i = 0; i < statics.size(); i++)
        {
            SDL_FillRect( surface, statics[i].getRekt(), statics[i].getColorNumber() );
        }
    }

    // Draw Menu
    if (menu_handler.inMenu())
    {
        // Draw Transparent Overlay
        SDL_Rect menu_box = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 }; 
        SDL_FillRect( surface, &menu_box, colorToNumber(MENU_BACKGROUND_COLOR) );
        // Get Options
        Menu menu = menu_handler.getMenu();
        std::vector< Option > *options = menu.getAllOptions();
        if (options->size() > 0)
        {
            int option_height = (menu_box.h - 60) / options->size();
            for (int i = 0; i < (int)options->size(); i++)
            {
                SDL_Rect option_box = { menu_box.x + 30, 
                                        menu_box.y + 30 + option_height * i,  
                                        menu_box.w - 60, 
                                        option_height };
                SDL_FillRect( surface, &option_box, colorToNumber((*options)[i].bg) );
            }
        }
    }
    SDL_UpdateWindowSurface( window );
}

void GameData::updateMap(int map_index)
{
    map_index = map_index;
    statics = world.getMap(map_index)->getSolids();
}

bool GameData::init()
{
    bool success = true; // proof by contradiction
    if (!world.loadMaps())
    {
        printf( "Maps couldn't be initialized! \n"); 
        success = false;
    }
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL couldn't be initialized! : %s\n", SDL_GetError() ); 
        success = false;
    }
    else
    {
        window = SDL_CreateWindow ( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
        if ( window == NULL )
        {
            printf( "Window couldn't be created! : %s\n", SDL_GetError() );
            success = false;
        }
        surface = SDL_GetWindowSurface( window );
    }
    initialized = true;
    return success;
}


bool GameData::close()
{
    bool success = true; // proof by contradiction
    // Deallocate the surface
    SDL_FreeSurface( surface );
    surface = NULL;

    // Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();

    printf("Goodbye!\n");

    return success;
}



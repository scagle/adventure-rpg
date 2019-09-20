#include <iostream>
#include <stdio.h>
#include <SDL.h>

#include "globals.hpp"
#include "ui/keyboard_handler.hpp"
#include "ui/menu_handler.hpp"
#include "objects/character.hpp"
#include "objects/world.hpp"
#include "utils/sdl_utils.hpp"

// Function Declarations
void updateMap(int map_index);
void update();
void render();
bool init();
bool close();
void checkInputs(SDL_Event*);

// Global Variables
SDL_Window* window = NULL;          // Window containing the game
SDL_Surface* surface = NULL;        // Surface being drawn to
SDL_Renderer *renderer = NULL;      // Hardware accelerated renderer

KeyboardHandler keyboard_handler;   // Keyboard input handler
MenuHandler menu_handler;           // Menu handler
Character main_character;           // Main character
World world;                        // World with all the maps

// Current Map attributes
std::vector< Solid > statics;
int map_index = 0;

bool initialized = false;
bool quit = false;
bool inMenu = true;

int main(int argc, char *argv[])
{
    if ( init() == false )
        return 1;

    updateMap(0);

    SDL_Event event;
    while ( !quit )
    {
        checkInputs(&event);
        update();
        render();
    }

    close();

    return 0;
} 

void updateMap(int map_index)
{
    map_index = map_index;
    statics = world.getMap(map_index)->getSolids();
}

void update()
{
    // Update Character
    float velocity_x = keyboard_handler.getHorizontal() * MAIN_CHARACTER_SPEED;
    float velocity_y = keyboard_handler.getVertical()   * MAIN_CHARACTER_SPEED;
    main_character.setVelocity(velocity_x, velocity_y);
    main_character.update(&statics);
}

void render()
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
        Menu menu = menu_handler.getMenu();
    }

    SDL_UpdateWindowSurface( window );
}

void checkInputs(SDL_Event* event)
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

bool init()
{
    bool success = true; // proof by contradiction
    keyboard_handler = KeyboardHandler();
    menu_handler = MenuHandler();
    main_character = Character( SDL_Rect{0, 0, 20, 20}, SDL_Color{255, 50, 50} );
    world = World();
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

bool close()
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


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <assert.h>
#include "gamedata.hpp"
#include "sdl_utils.hpp"
#include "event.hpp"
#include "text_box.hpp"
#include "button_box.hpp"
#include "enums/direction.hpp"
#include "enums/event_type.hpp"
#include "container.hpp"

namespace game
{

    // Static Declarations
    SDL_Renderer* GameData::renderer;         
    std::vector< TTF_Font* > GameData::fonts; 
    std::vector< Solid > *GameData::solids;
    std::vector< Solid > *GameData::portals;
    bool GameData::initialized = false;
    bool GameData::quit = false;
    std::unordered_map< std::string, Container > mapping;

    GameData::~GameData()
    {
        close(); 
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
                    default: 
                        break;
                }
            }
            ui_manager.handleInput(event);
            keyboard_handler.handleInput(event);
        }
    }

    void GameData::update()
    {
        if (!ui_manager.inUI(UI::MENU))
        {
            // Update Character
            float velocity_x = keyboard_handler.getHorizontal() * MAIN_CHARACTER_SPEED;
            float velocity_y = keyboard_handler.getVertical()   * MAIN_CHARACTER_SPEED;
            main_character.setVelocity(velocity_x, velocity_y);
            main_character.update();
            world.update();
        }
    }

    void GameData::render()
    {
        // Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear( renderer );

        // Render Environment
        world.render( renderer );
        main_character.render( renderer );

        // Render Menu
        ui_manager.render( renderer );

        //Update screen
        SDL_RenderPresent( renderer );
    }

    void GameData::updateMap( int map_index )
    {
        map_index = map_index;
        Environment *env = world.getMap(map_index);
        solids = env->getSolids();
        portals = env->getPortals();
    }
    
    bool GameData::close()
    {
        bool success = true; // proof by contradiction

        printf("Closing GameData!\n");
        // Destroy window
        SDL_DestroyWindow( window );
        SDL_DestroyRenderer( renderer );
        window = NULL;
        renderer = NULL;

        for ( TTF_Font* font : fonts )
        {
            TTF_CloseFont(font);
        }

        TTF_Quit();
        SDL_Quit();

        printf("Goodbye!\n");

        return success;
    }

    void GameData::start()
    {
        if ( init() )
            std::cout << "Initialization Success!" << "\n";
        else
            std::cout << "Initialization Failure!" << "\n";
        main_character = Character( SDL_Rect{15, 50, 20, 20}, SDL_Color{255, 50, 50, 255}, MAIN_CHARACTER_NAME, true );
    }

    bool GameData::init()
    {
        if ( !initSDL() )
            printf("Initialization of initSDL() failed!\n");
        if ( !initSDL_Window() )
            printf("Initialization of initSDL_Window() failed!\n");
        if ( !initSDL_Renderer() )
            printf("Initialization of initSDL_Renderer() failed!\n");
        if ( !initFonts() )
            printf("Initialization of initFonts() failed!\n");
        if ( !initWorlds() )
            printf("Initialization of initWorlds() failed!\n");
        if ( !initUI() )
            printf("Initialization of initUI() failed!\n");

        initialized = true;
        return true;
    }

    bool GameData::initSDL()
    {
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL couldn't be initialized! : %s\n", SDL_GetError() ); 
            return false;
        }
        return true;
    }

    bool GameData::initSDL_Window()
    {
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
        return true;
    }

    bool GameData::initSDL_Renderer()
    {
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        //SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );
        if ( renderer == NULL )
        {
            printf( "Renderer couldn't be created! : %s\n", SDL_GetError() );
            return false;
        }
        return true;
    }

    bool GameData::initFonts()
    {
        if ( TTF_Init() == -1 )
        {
            printf( "Fonts couldn't be initialized! \n" ); 
            return false;
        }
        std::vector< std::string > font_names = {
            "../assets/fonts/NotoSansMono-Regular.ttf", 
            "../assets/fonts/Sauce_Code_Pro_Medium_Nerd_Font_Complete_Mono.ttf",
            "../assets/fonts/lazy.ttf", 
        };
        for ( std::string font_name : font_names )
        {
            TTF_Font *font = TTF_OpenFont(font_name.c_str(), 32);
            if ( font == NULL )
            {
                printf( "Font: '%s' couldn't be found! \n", font_name.c_str() ); 
                return false;
            }
            fonts.push_back(font);
        }
        return true;
    }

    bool GameData::initWorlds()
    {
        if ( !world.loadMaps() )
        {
            printf( "Maps couldn't be initialized! \n"); 
            return false;
        }
        return true;
    }

    bool GameData::initUI()
    {

        if ( !ui_manager.initializeUIHandlers() )
        {
            printf( "UI Manager couldn't initialize handlers!\n"); 
            return false;
        }
        return true;
    }
};

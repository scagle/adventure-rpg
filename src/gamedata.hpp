#pragma once

// Forward Declarations
namespace game
{
    class Solid;
    class Event;
};
class SDL_Window;
class SDL_Renderer;
union SDL_Event;

#include "keyboard_handler.hpp"
#include "ui_manager.hpp"
#include "world.hpp"
#include "character.hpp"
#include "solid.hpp"

#include "external/SDL_FontCache.h"
#include "enums/event_type.hpp"

#include <bitset>
#include <vector>
#include <SDL_ttf.h>

namespace game
{
    class GameData
    {
        private:
            SDL_Window* window;                 // Window containing the game
            KeyboardHandler keyboard_handler;   // Keyboard input handler
            UIManager ui_manager;               // Manager of menus/dialogs/travel interfaces
            World world;                        // World with all the maps / mapdata

            static SDL_Renderer* renderer;          // Hardware accelerated renderer
            static std::vector< FC_Font* > fonts;  // All pre-loaded fonts
            static bool initialized;
            static bool quit;

        public:
            GameData() { }
            ~GameData();
            bool isDone() const { return quit; }
            void checkInputs( SDL_Event* event );
            void update();
            void render();
            void updateMap( std::string id );
            bool close();

            static void sendEvent(Event, bool);
            static bool getInitialized() { return initialized; }
            static bool getQuit() { return quit; }
            static FC_Font* getFont( int i ) { return fonts[i]; }
            static SDL_Renderer* getActiveRenderer() { return renderer; }
            static void setInitialized(bool val) { initialized = val; }

            void startGame(); // Non-static on purpose
            static void restartGame();
            static void quitGame() { quit = true; }

            bool initGame();
            bool initSDL();
            bool initSDL_Window();
            bool initSDL_Renderer();
            bool initFonts();
            bool initWorlds();
            bool initUI();
    };
};

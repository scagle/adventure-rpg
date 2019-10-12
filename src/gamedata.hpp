#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <bitset>
#include <vector>
#include "keyboard_handler.hpp"
#include "ui_manager.hpp"
#include "world.hpp"
#include "character.hpp"
#include "event.hpp"
#include "solid.hpp"
#include "enums/event_type.hpp"


class KeyboardHandler;
class MenuHandler;
class Character;
class World;
class Solid;

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
            static std::vector< TTF_Font* > fonts;  // All pre-loaded fonts
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
            static TTF_Font* getFont(int) { return fonts[0]; }
            static SDL_Renderer* getActiveRenderer() { return renderer; }
            static void setInitialized(bool val) { initialized = val; }
            static void setQuit(bool val) { quit = val; }

            void start();
            void restart();
            bool init();
            bool initSDL();
            bool initSDL_Window();
            bool initSDL_Renderer();
            bool initFonts();
            bool initWorlds();
            bool initUI();
    };
};

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <bitset>
#include <vector>
#include "keyboard_handler.hpp"
#include "menu_handler.hpp"
#include "character.hpp"
#include "world.hpp"
#include "event.hpp"
#include "solid.hpp"


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
            SDL_Window* window;          // Window containing the game
            KeyboardHandler keyboard_handler;   // Keyboard input handler
            MenuHandler menu_handler;           // Menu handler
            Character main_character;           // Main character
            World world;                        // World with all the maps

            // Current Map attributes
            int map_index = 0;

            static SDL_Renderer* renderer;          // Hardware accelerated renderer
            static std::vector< TTF_Font* > fonts;  // Fonts
            static std::vector< Solid > *solids;    // A pointer to a vector of solids
            static std::vector< Solid > *portals;   // A vector of pointers to solids that are of type PORTAL
            static bool initialized;
            static bool quit;

        public:
            GameData() { }
            ~GameData();
            bool isDone() const { return quit; }
            void checkInputs( SDL_Event* event );
            void update();
            void render();
            void updateMap(int map_index);
            bool close();

            static void sendEvent(Event, bool);
            static bool inEvent(Event::Game_EventType type) { return Event::inEvent(type); }
            static bool getInitialized() { return initialized; }
            static bool getQuit() { return quit; }
            static std::vector< Solid >* getSolids() { return solids; }
            static std::vector< Solid >* getPortals() { return portals; }
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
            bool initMenus();
    };
}

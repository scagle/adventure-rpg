#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <vector>
#include "keyboard_handler.hpp"
#include "menu_handler.hpp"
#include "character.hpp"
#include "world.hpp"
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
            std::vector< Solid > statics;
            int map_index = 0;
            bool inMenu = true;

            static SDL_Renderer* renderer;          // Hardware accelerated renderer
            static std::vector< TTF_Font* > fonts;  // Fonts
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
            static bool getInitialized() { return initialized; }
            static bool getQuit() { return quit; }
            static TTF_Font* getDefaultFont(int) { return fonts[0]; }
            static SDL_Renderer* getActiveRenderer() { return renderer; }
            static void setInitialized(bool val) { initialized = val; }
            static void setQuit(bool val) { quit = val; }
            void start();
            void restart();
            bool init();
            bool initSDL();
            bool initSDL_Window();
            bool initSDL_Renderer();
            bool initMaps();
            bool initFonts();
            bool initWorlds();
            bool initMenus();
    };
}

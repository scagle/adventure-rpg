#include <SDL.h>
#include "ui/keyboard_handler.hpp"
#include "ui/menu_handler.hpp"
#include "objects/character.hpp"
#include "objects/world.hpp"
#include "objects/solid.hpp"


class KeyboardHandler;
class MenuHandler;
class Character;
class World;
class Solid;

class GameData
{
    private:
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

    public:
        GameData();
        bool isDone() const { return quit; }
        void checkInputs( SDL_Event* event );
        void update();
        void render();
        void updateMap(int map_index);
        bool init();
        bool close();
};

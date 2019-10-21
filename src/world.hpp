#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include "environment.hpp"
#include "character.hpp"
#include "dynamic_character.hpp"
#include "main_character.hpp"

namespace game
{
    // World is used to keep track of all the different maps, and variables 
    // associated with the story
    class World
    {
        private:
        static std::unordered_map< std::string, Environment > maps;
        static Environment* current_map;   
        static MainCharacter main_character;   

        public:
        World();
        ~World() { }
        bool loadMaps(); 
        static void updateMap( std::string id, int entry );
        
        static Environment* getCurrentMap() { return current_map; }
        static std::vector< Solid >* getSolids() { return getCurrentMap()->getSolids(); }
        static std::vector< Solid >* getPortals() { return getCurrentMap()->getPortals(); }
        static std::vector< Character >* getCharactersInMap() { return current_map->getCharacters(); }
        static SDL_Color* getCurrentBackground() { return current_map->getBackground(); }
        static void changeMap( std::string id ) { current_map = &(maps[id]); }

        std::vector< std::string > getFiles(std::string, std::string); 
        std::vector< Character* >* getCharacters(); // TODO: Recursively check all environments and return characters

        static void setMainCharacterVelocity( float velocity_x, float velocity_y );

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

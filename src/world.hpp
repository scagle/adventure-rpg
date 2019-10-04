#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "environment.hpp"
#include "character.hpp"

namespace game
{
    // World is used to keep track of all the different maps, and variables 
    // associated with the story
    class World
    {
        private:
        static std::vector< Environment > maps;
        static unsigned int current_map;   

        public:
        World();
        ~World() { }
        bool loadMaps(); 
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        Environment* getCurrentMap() { return &(this->maps[current_map]); }
        Environment* getMap(unsigned int index) { return &(this->maps[index]); }

        static std::vector< Character >* getCharactersInMap() { return maps[current_map].getCharacters(); }
        std::vector< std::string > getFiles(std::string, std::string); 
        std::vector< Character* >* getCharacters(); // TODO: Recursively check all environments and return characters
        
    };
};

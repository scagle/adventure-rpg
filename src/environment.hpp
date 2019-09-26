#pragma once

#include <vector>
#include <string>
#include <SDL.h>
#include "solid.hpp"
#include "character.hpp"

namespace game
{
    class Environment
    {
        private:
        std::string name;
        std::vector< Solid > solids;
        std::vector< Solid > portals;
        std::vector< Character > characters;

        public:
        Environment() { }
        Environment(std::string n, std::vector< Solid > o, std::vector< Solid > p, std::vector< Character > c) : 
            name(n), solids(o), portals(p), characters(c) { }
        ~Environment() { }

        virtual void render( SDL_Renderer *renderer );
        virtual void update();

        std::vector< Solid >* getSolids() { return &solids; }
        std::vector< Solid >* getPortals() { return &portals; }
        std::vector< Character >* getCharacters() { return &characters; }
    };
}

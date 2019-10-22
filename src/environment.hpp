#pragma once

#include <vector>
#include <string>
#include <SDL.h>
#include "solid.hpp"
#include "character.hpp"
#include "dynamic_character.hpp"
#include "datatypes/position.hpp"

namespace game
{
    class Environment
    {
        private:
        std::string name;
        SDL_Color background;
        std::vector< Solid > solids;
        std::vector< Solid > portals;
        std::vector< Character > characters;
        std::vector< DynamicCharacter > dynamics;
        std::vector< Position > entries;

        public:
        Environment() { }

        Environment( std::string n, SDL_Color bg, std::vector< Solid > o, std::vector< Solid > p, 
                     std::vector< Character > c, std::vector< DynamicCharacter > dc, std::vector< Position > entries ) 
            : name(n), background(bg), solids(o), portals(p), characters(c), dynamics(dc), entries(entries) { }

        ~Environment() { }

        virtual void render( SDL_Renderer *renderer );
        virtual void update();

        SDL_Color* getBackground() { return &background; }
        std::vector< Solid >* getSolids() { return &solids; }
        std::vector< Solid >* getPortals() { return &portals; }
        std::vector< Character >* getCharacters() { return &characters; }
        Position* getEntry( int entry ) { return &(entries[entry]); }
    };
};

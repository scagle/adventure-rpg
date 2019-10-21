#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "solid.hpp" 
#include "character.hpp" 

namespace game
{
    class MainCharacter : public DynamicCharacter
    {
        void checkPortals( std::vector< Solid > * );
        void checkNPCs( std::vector< Character > * );
        std::vector< Character* > getAdjacentNPCs( std::vector< Character > *characters );

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

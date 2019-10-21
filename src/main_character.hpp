#pragma once
#include <vector>
#include <SDL.h>
#include "solid.hpp" 
#include "character.hpp" 
#include "dynamic_character.hpp" 

namespace game
{
    class MainCharacter : public DynamicCharacter
    {

        public:
        MainCharacter();
        MainCharacter( SDL_Rect, SDL_Color, std::string );
        virtual ~MainCharacter() { }

        void checkPortals( std::vector< Solid > * );
        void checkNPCs( std::vector< Character > * );
        std::vector< Character* > getAdjacentNPCs( std::vector< Character > *characters );

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

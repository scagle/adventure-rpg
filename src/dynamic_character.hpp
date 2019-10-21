#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "solid.hpp" 
#include "character.hpp" 

namespace game
{
    // Moveable/Animated Character ( Collidable or not )
    class DynamicCharacter : public Character
    {
        float actual_x; 
        float actual_y;
        float velocity_x;
        float velocity_y;

        bool moveCharacter( float *, float *, int *, int *, std::vector< Solid > *, int );

        void setVelocity( float vx, float vy ) { velocity_x = vx; velocity_y = vy; }
        void setPosition( Position* pos) { this->actual_x = pos->x; this->actual_y = pos->y; }

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

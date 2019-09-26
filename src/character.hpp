#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "solid.hpp" 

namespace game
{
    class Character : public Solid
    {
        private:
        float actual_x; 
        float actual_y;
        float velocity_x;
        float velocity_y;
        std::string name;

        public:
        Character();
        Character(SDL_Rect, SDL_Color, std::string);
        virtual void update();
        virtual void render( SDL_Renderer *renderer );
        // Accessors
        // Mutators
        void setVelocity(float vx, float vy){ velocity_x = vx; velocity_y = vy; } 
    };
}

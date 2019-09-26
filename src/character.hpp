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
        bool main_character;

        public:
        Character();
        Character(SDL_Rect, SDL_Color, std::string);
        Character(SDL_Rect, SDL_Color, std::string, bool);
        void construct(SDL_Rect, SDL_Color, std::string, bool); // constructor wrapper

        bool moveCharacter(float *, float *, int *, int *, std::vector< Solid > *, int);
        void checkPortal(std::vector< Solid > *);
        virtual void update();
        virtual void render( SDL_Renderer *renderer );
        // Accessors
        // Mutators
        void setVelocity(float vx, float vy){ velocity_x = vx; velocity_y = vy; } 
    };
}

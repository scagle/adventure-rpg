#pragma once

#include <vector>
#include <SDL.h>

#include "solid.hpp" 

class Character : public Solid
{
    private:
    float actual_x = 0; 
    float actual_y = 0;
    float velocity_x = 0;
    float velocity_y = 0;

    public:
    Character();
    Character(SDL_Rect, SDL_Color);
    void update(std::vector< Solid >*);
    // Accessors
    // Mutators
    void setVelocity(float vx, float vy){ velocity_x = vx; velocity_y = vy; } 
};

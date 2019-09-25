#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "character.hpp"
#include "globals.hpp"

namespace game
{
    Character::Character()
    {
        this->hitbox = {0, 0, 5, 5};
    }

    Character::Character(SDL_Rect hitbox, SDL_Color color)
    {
        this->hitbox = hitbox;
        this->color = color;
    }

    void Character::update(std::vector< Solid > *statics)
    {
        // Update position and check collisions
        float prev_x = this->actual_x;
        float prev_y = this->actual_y;
        this->actual_x += this->velocity_x;
        this->actual_y += this->velocity_y;
        if ( std::abs( prev_x - this->hitbox.x ) > 0) // X Component 
        {
            this->hitbox.x = (int)(this->actual_x + 0.5); // Rounding to nearest whole number
            bool bounce = false;
            if ( this->hitbox.x < 0 || this->hitbox.x + this->hitbox.w > SCREEN_WIDTH )
            {
                bounce = true; 
            }
            else
            {
                if ( statics != NULL )
                {
                    for ( unsigned int i = 0; i < statics->size(); i++ )
                    {
                        if ( SDL_HasIntersection( &(this->hitbox), &((*statics)[i].hitbox) ) )
                        {
                            bounce = true;
                            break;
                        }
                    }
                }
            }
            if ( bounce )
            {
                this->actual_x = prev_x;
                this->hitbox.x = (int)(this->actual_x + 0.5); // Rounding to nearest whole number
            }
        }
        if ( std::abs( prev_y - this->hitbox.y ) > 0) // Y Component
        {
            this->hitbox.y = (int)(this->actual_y + 0.5); // Rounding to nearest whole number
            bool bounce = false;
            if ( this->hitbox.y < 0 || this->hitbox.y + this->hitbox.h > SCREEN_HEIGHT )
            {
                bounce = true; 
            }
            else
            {
                if ( statics != NULL )
                {
                    for ( unsigned int i = 0; i < statics->size(); i++ )
                    {
                        if ( SDL_HasIntersection( &(this->hitbox), &((*statics)[i].hitbox) ) )
                        {
                            bounce = true;
                            break;
                        }
                    }
                }
            }
            if ( bounce )
            {
                this->actual_y = prev_y;
                this->hitbox.y = (int)(this->actual_y + 0.5); // Rounding to nearest whole number
            }
        }
    }

    void Character::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &hitbox );
    }
}

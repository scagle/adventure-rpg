#include "dynamic_character.hpp"

#include "world.hpp"
#include "solid.hpp"
#include "character.hpp"
#include "globals.hpp"

namespace game
{
    DynamicCharacter::DynamicCharacter()
        : Character( )
    {
        construct( {0, 0, 10, 10} );
    }

    DynamicCharacter::DynamicCharacter( SDL_Rect hitbox, SDL_Color color, std::string name )
        : Character( hitbox, color, name )
    {
        construct( hitbox );
    }

    void DynamicCharacter::construct( SDL_Rect hitbox )
    {
        this->actual_x = hitbox.x; 
        this->actual_y = hitbox.y;
        this->velocity_x = 0;
        this->velocity_y = 0;
    }
    // Function to move character while detecting collisions with solids
    // actual = actual_x/y, velocity = velocity_x/y, solids = solids
    // returns boolean of whether it bounced or not
    bool DynamicCharacter::moveCharacter( float *actual, float *velocity, int *hitbox_coord, 
            int *hitbox_offset, std::vector< Solid > *solids, int boundary )
    {
        float prev = *actual; // Record original value;
        bool bounce = false;
        // Move character
        *actual += *velocity; // Update "actual" position (float instead of int)
        if ( std::abs( prev - *hitbox_coord ) > 0) // If we have visually moved a pixel
        {
            *hitbox_coord = (int)(*actual + 0.5); // Round actual pos to nearest pixel pos
            // Detect Collisions
            if ( *hitbox_coord < 0 || *hitbox_coord + *hitbox_offset > boundary )
            {
                bounce = true; 
            }
            else
            {
                if ( solids != NULL )
                {
                    for ( unsigned int i = 0; i < solids->size(); i++ )
                    {
                        if ( SDL_HasIntersection( &(this->hitbox), (*solids)[i].getRekt() ) )
                        {
                            bounce = true;
                            break;
                        }
                    }
                }
            }
            if ( bounce )
            {
                *actual = prev;
                *hitbox_coord = (int)(*actual + 0.5); // Rounding to nearest whole number
            }
        }

        return bounce;
    }

    void DynamicCharacter::render( SDL_Renderer *renderer )
    {
        Character::render( renderer );
    }

    void DynamicCharacter::update()
    {
        Character::update();
        std::vector< Solid > *solids = World::getSolids();
        // Move Character
        moveCharacter(&actual_x, &velocity_x, &(hitbox.x), &(hitbox.w), solids, SCREEN_WIDTH);
        moveCharacter(&actual_y, &velocity_y, &(hitbox.y), &(hitbox.h), solids, SCREEN_HEIGHT);
        
    }
};

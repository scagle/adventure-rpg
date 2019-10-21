#include "dynamic_character.hpp"

namespace DynamicCharacter
{
    // Function to move character while detecting collisions with solids
    // actual = actual_x/y, velocity = velocity_x/y, solids = solids
    // returns boolean of whether it bounced or not
    bool Character::moveCharacter( float *actual, float *velocity, int *hitbox_coord, 
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
                        if ( SDL_HasIntersection( &(this->hitbox), &((*solids)[i].hitbox) ) )
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
};

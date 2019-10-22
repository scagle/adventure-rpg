#include "dynamic_character.hpp"

#include "world.hpp"
#include "solid.hpp"
#include "character.hpp"
#include "datatypes/position.hpp"
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

    DynamicCharacter::DynamicCharacter( SDL_Rect hitbox, SDL_Color color, std::string name, std::string action )
        : Character( hitbox, color, name, action )
    {
        construct( hitbox );
    }

    DynamicCharacter::DynamicCharacter( SDL_Rect hitbox, SDL_Color color, std::string name, Behavior behavior )
        : Character( hitbox, color, name )
    {
        construct( hitbox );
        this->behavior = behavior;
    }

    DynamicCharacter::DynamicCharacter( SDL_Rect hitbox, SDL_Color color, std::string name, std::string action, 
                                        Behavior behavior )
        : Character( hitbox, color, name )
    {
        construct( hitbox );
        this->behavior = behavior;
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

    void DynamicCharacter::performBehavior( MainCharacter *main_character )
    {
        // Mathy stuff
        SDL_Rect *main_hitbox = main_character->getRekt(); 
        Position main_pos = Position( main_hitbox->x + main_hitbox->w / 2, main_hitbox->y + main_hitbox->h / 2 );
        Position this_pos = Position( hitbox.x + hitbox.w / 2, hitbox.y + hitbox.h / 2 );
        double delta_x = this_pos.x - main_pos.x;      // Difference in X position
        double delta_y = this_pos.y - main_pos.y;      // Difference in Y position
        if (delta_x == 0 || delta_y == 0 )
        {
            if ( delta_x == 0 && delta_y == 0 )
            {
                setVelocity( 0, 0 );
            }
            else if ( delta_x == 0 )
            {
                if ( delta_y > 0 )
                {
                    setVelocity( 0, -speed );
                }
                else
                {
                    setVelocity( 0, speed );
                }
            }
            else if ( delta_y == 0 )
            {
                if ( delta_x > 0 )
                {
                    setVelocity( -speed, 0 );
                }
                else
                {
                    setVelocity( speed, 0 );
                }
            }
            return;
        }
        double angle = std::atan( delta_x / delta_y ); // Angle in radians
        double unit_velocity_x, unit_velocity_y;
        if ( delta_y > 0 )
        {
            unit_velocity_x = (-1) * std::sin( angle ) * speed;
            unit_velocity_y = (-1) * std::cos( angle ) * speed;
        }
        else
        {
            unit_velocity_x = std::sin( angle ) * speed;
            unit_velocity_y = std::cos( angle ) * speed;
        }

        // Perform Behavior
        switch ( behavior )
        {
            case Behavior::NONE:
            {
                break;
            }
            case Behavior::LOCAL_FOLLOW:
            {
                if ( getDistance( main_pos.x, main_pos.y, DISTANCE_FAST ) <= local_radius )
                {
                    setVelocity( ( float )( unit_velocity_x ), ( float )( unit_velocity_y ) );
                }
                break;
            }
            case Behavior::GLOBAL_FOLLOW:
            {
                setVelocity( ( float )( unit_velocity_x ), ( float )( unit_velocity_y ) );
                break;
            }
            case Behavior::LOCAL_FLEE:
            {
                if ( getDistance( main_pos.x, main_pos.y, DISTANCE_FAST ) <= local_radius )
                {
                    setVelocity( ( float )( -unit_velocity_x ), ( float )( -unit_velocity_y ) );
                }
                break;
            }
            case Behavior::GLOBAL_FLEE:
            {
                setVelocity( ( float )( -unit_velocity_x ), ( float )( -unit_velocity_y ) );
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void DynamicCharacter::render( SDL_Renderer *renderer )
    {
        Character::render( renderer );
    }

    void DynamicCharacter::update()
    {
        Character::update();
        if ( behavior != Behavior::NONE )
        {
            std::vector< Solid > *solids = World::getSolids();
            MainCharacter *main_character = World::getMainCharacter();

            performBehavior( main_character ); // Update velocities based on behavior

            // Move Character
            DynamicCharacter::moveCharacter(&actual_x, &velocity_x, &(hitbox.x), &(hitbox.w), solids, SCREEN_WIDTH);
            DynamicCharacter::moveCharacter(&actual_y, &velocity_y, &(hitbox.y), &(hitbox.h), solids, SCREEN_HEIGHT);
        }
    }
};

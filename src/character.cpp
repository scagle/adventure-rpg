#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "character.hpp"
#include "gamedata.hpp"
#include "globals.hpp"

namespace game
{
    Character::Character()
    {
        this->hitbox = {0, 0, 5, 5};
        this->actual_x = hitbox.x; 
        this->actual_y = hitbox.y;
        this->velocity_x = 0;
        this->velocity_y = 0;
        this->color = {200, 200, 200, 255};
        this->name = "UNDEFINED"; 
    }

    Character::Character(SDL_Rect hitbox, SDL_Color color, std::string name)
    {
        this->hitbox = hitbox;
        this->actual_x = hitbox.x; 
        this->actual_y = hitbox.y;
        this->velocity_x = 0;
        this->velocity_y = 0;
        this->color = color;
        this->name = name; 
    }

    void Character::update()
    {
        std::vector< Solid > *solids =  GameData::getSolids();
        std::vector< Solid > *portals =  GameData::getPortals();
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
                this->actual_y = prev_y;
                this->hitbox.y = (int)(this->actual_y + 0.5); // Rounding to nearest whole number
            }
        }

        /*! TODO: This
         *  \todo This
         */
        // Check portals
        bool was_inside = GameData::inEvent( Event::Game_EventType::PORTAL );
        bool is_inside = false;
        for (unsigned int i = 0; i < (*portals).size(); i++)
        {
            if ( isInside(&((*portals)[i].hitbox)) )
            {
                is_inside = true;
                if ( !was_inside )
                {
                    GameData::sendEvent(Event(Event::Game_EventType::PORTAL, "forest"), true); // Send "PORTAL" event
                    break;
                }
            }
        }
        if ( was_inside && !is_inside )
        {
            GameData::sendEvent(Event(Event::Game_EventType::PORTAL, ""), false); // Send "PORTAL" event
        }
    }

    void Character::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &hitbox );
    }
}

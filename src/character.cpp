#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <cstdlib>

#include "character.hpp"
#include "gamedata.hpp"
#include "menu_handler.hpp"
#include "world.hpp"
#include "globals.hpp"

namespace game
{
    Character::Character()
    {
        construct({0, 0, 5, 5}, {200, 200, 200, 255}, "UNDEFINED", false, "");
    }

    Character::Character(SDL_Rect hitbox, SDL_Color color, std::string name)
    {
        construct(hitbox, color, name, false, "");
    }

    Character::Character(SDL_Rect hitbox, SDL_Color color, std::string name, bool mc)
    {
        construct(hitbox, color, name, mc, "");
    }

    Character::Character(SDL_Rect hitbox, SDL_Color color, std::string name, bool mc, std::string action)
    {
        construct(hitbox, color, name, mc, action);
    }

    void Character::construct(SDL_Rect hitbox, SDL_Color color, std::string name, bool mc, std::string action)
    {
        this->hitbox = hitbox;
        this->actual_x = hitbox.x; 
        this->actual_y = hitbox.y;
        this->velocity_x = 0;
        this->velocity_y = 0;
        this->color = color;
        this->name = name; 
        this->main_character = mc; 
        this->action = action; 
    }

    // Function to move character while detecting collisions with solids
    // actual = actual_x/y, velocity = velocity_x/y, solids = solids
    // returns boolean of whether it bounced or not
    bool Character::moveCharacter(float *actual, float *velocity, int *hitbox_coord, 
            int *hitbox_offset, std::vector< Solid > *solids, int boundary)
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

    void Character::checkPortal(std::vector< Solid > *portals)
    {
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

    void Character::checkNearby(std::vector< Character > *characters)
    {
        //TODO: Make pushDialog/pushMenu push copy of dialog/menu so that more than one of them can appear.
        //      Also see if you can make the Font_Textures static, so that they don't have to be created
        //      everytime a new dialog/menu is created
        bool was_inside = MenuHandler::inDialog();
        bool is_inside = false;
        Character *closest_character;
        unsigned int distance = 100;
        std::string action = "";
        for ( unsigned int i = 0; i < characters->size(); i++ )
        {
            unsigned int temp_distance = (*characters)[i].getDistance(actual_x, actual_y, DISTANCE_FAST);
            if ( temp_distance < distance && (*characters)[i].hasDialog() )
            {
                distance = temp_distance;
                closest_character = &((*characters)[i]);
                action = (*characters)[i].getAction();
                is_inside = true;
            }
        }
        if (!was_inside && is_inside)
        {
            MenuHandler::pushDialog("shop0_buy", 0, 0);
            //printf("Inside Area\n");
        }
        if (was_inside && !is_inside)
        {
            //MenuHandler::pushDialog("shop0_buy", 0, 0);
            //printf("Left Area\n");
        }
    }

    unsigned int Character::getDistance(float x, float y, Distance_Algorithm alg)
    {
        unsigned int distance;
        if (alg == DISTANCE_FAST)
        {
            int distance_x = abs((int)(actual_x + 0.5) - (int)(x + 0.5));
            int distance_y = abs((int)(actual_y + 0.5) - (int)(y + 0.5));
            distance = distance_x + distance_y;
        }
        if (alg == DISTANCE_ACCURATE)
        {
            distance = 0;
            printf("Unimplemented DISTANCE_ACCURATE");
        }
        return distance; 
    }

    void Character::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &hitbox );
    }

    void Character::update()
    {
        if (main_character)
        {
            std::vector< Solid > *solids = GameData::getSolids();
            std::vector< Solid > *portals = GameData::getPortals();
            std::vector< Character > *characters = World::getCharactersInMap();

            // Move Character
            moveCharacter(&actual_x, &velocity_x, &(hitbox.x), &(hitbox.w), solids, SCREEN_WIDTH);
            moveCharacter(&actual_y, &velocity_y, &(hitbox.y), &(hitbox.h), solids, SCREEN_WIDTH);

            // Check if inside Portals
            checkPortal(portals);

            // Check if near NPC's
            checkNearby(characters);
        }
    }

}

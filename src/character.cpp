#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <cstdlib>

#include "character.hpp"
#include "gamedata.hpp"
#include "ui_manager.hpp"
#include "dialog_handler.hpp"
#include "travel_handler.hpp"
#include "world.hpp"
#include "globals.hpp"
#include "enums/event_type.hpp"

namespace game
{
    Character::Character()
    {
        construct({0, 0, 5, 5}, {200, 200, 200, 255}, "UNDEFINED", false, "");
    }

    Character::Character( SDL_Rect hitbox, SDL_Color color, std::string name )
    {
        construct(hitbox, color, name, false, "");
    }

    Character::Character( SDL_Rect hitbox, SDL_Color color, std::string name, bool mc )
    {
        construct(hitbox, color, name, mc, "");
    }

    Character::Character( SDL_Rect hitbox, SDL_Color color, std::string name, bool mc, std::string action )
    {
        construct(hitbox, color, name, mc, action);
    }

    void Character::construct( SDL_Rect hitbox, SDL_Color color, std::string name, bool mc, std::string action )
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

    void Character::checkPortals( std::vector< Solid > *portals )
    {
        if ( !UIManager::inUI(UI::TRAVEL) && portals->size() > 0 )
        {
            if ( focused_portal != NULL )
            {
                if ( !isInside( &(focused_portal->hitbox) ) )
                {
                    sendEvent( EventType::TRAVEL, UI::TRAVEL, focused_portal->getLocation(), 0 );
                    focused_portal = NULL;
                }
            }
            else
            {
                for ( unsigned int i = 0; i < (*portals).size(); i++ )
                {
                    if ( isInside(&((*portals)[i].hitbox)) )
                    {
                        focused_portal = &((*portals)[i]);
                        printf("location: %s\n", focused_portal->getLocation().c_str());
                        sendEvent( EventType::TRAVEL, UI::TRAVEL, focused_portal->getLocation(), 1 );
                        break;
                    }
                }
            }
        }
    }

    void Character::checkNPCs( std::vector< Character > *characters )
    {
        if ( !UIManager::inUI(UI::DIALOG) && characters->size() > 0 )
        {
            if ( focused_character != NULL )
            {
                unsigned int distance = getDistance(focused_character->getCenterX(), 
                                           focused_character->getCenterY(), DISTANCE_FAST );
                if ( distance > focused_character->getVoiceDistance())
                {
                    sendEvent(EventType::DIALOG, UI::DIALOG, focused_character->getAction(), 0);
                    focused_character = NULL;
                }
            }
            else
            {
                // Check if near any NPC's with dialog
                focused_character = getAdjacentNPC(characters);
                if ( focused_character != NULL )
                {
                    sendEvent(EventType::DIALOG, UI::DIALOG, focused_character->getAction(), 1);
                }
            }
        }
    }

    Character* Character::getAdjacentNPC( std::vector< Character > *characters )
    {
        //TODO: Make pushDialog/pushMenu push copy of dialog/menu so that more than one of them can appear.
        //      Also see if you can make the Font_Textures static, so that they don't have to be created
        //      everytime a new dialog/menu is created
        Character *closest_character = NULL;
        unsigned int closest_distance = 1000; // start at some high number
        for ( unsigned int i = 0; i < characters->size(); i++ )
        {
            if ( (*characters)[i].hasDialog() )
            {
                unsigned int distance_from_npc = (*characters)[i].getDistance(actual_x, actual_y, DISTANCE_FAST);
                if ( distance_from_npc < closest_distance && distance_from_npc <= (*characters)[i].getVoiceDistance() )
                {
                    closest_character = &((*characters)[i]);
                }
            }
        }
         
        return closest_character;
    }

    unsigned int Character::getDistance( float x, float y, Distance_Algorithm alg )
    {
        unsigned int distance = 0;
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

    void Character::sendEvent(EventType type, UI ui, std::string action, int value)
    {
        Event event = Event( type, action, value );
        if ( UIManager::handleEvent( ui, &event ) == false )
        {
            printf("Can't find event id '%s'", event.getID().c_str());
        }
    }

    void Character::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &hitbox );
    }

    void Character::update()
    {
        if ( main_character == true )
        {
            std::vector< Solid > *solids = GameData::getSolids();
            std::vector< Solid > *portals = GameData::getPortals();
            std::vector< Character > *characters = World::getCharactersInMap();

            // Move Character
            moveCharacter(&actual_x, &velocity_x, &(hitbox.x), &(hitbox.w), solids, SCREEN_WIDTH);
            moveCharacter(&actual_y, &velocity_y, &(hitbox.y), &(hitbox.h), solids, SCREEN_HEIGHT);

            // Check if inside Portals
            checkPortals(portals);

            // NPC dialog checks
            checkNPCs(characters);
        }
    }

};

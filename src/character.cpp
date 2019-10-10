#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <SDL.h>
#include <cstdlib>
#include <algorithm>

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

    std::vector< Solid* > adjacent_portals; 
    void Character::checkPortals( std::vector< Solid > *portals )
    {
        if ( portals->size() > 0 )
        {
            // Check for entering portal range
            std::vector< Solid* > new_adjacent_portals;
            for ( auto& portal : *portals)
            {
                if ( isInside( &(portal.hitbox) ) )
                {
                    new_adjacent_portals.push_back(&portal);
                }
            }

            for ( Solid* portal : new_adjacent_portals )
            {
                // if a new portal not found in adjacent_portals
                if ( std::find( adjacent_portals.begin(), adjacent_portals.end(), portal ) 
                     == adjacent_portals.end() )
                {
                    // Send found event
                    spawnTravel( portal->getLocation() );
                    printf("Entering portal '%s'\n", portal->getLocation().c_str());
                }
            }

            // Check for leaving portal range
            for ( Solid* portal : adjacent_portals)
            {
                // if an old portal not found in new_adjacent_portals
                if ( std::find( new_adjacent_portals.begin(), new_adjacent_portals.end(), portal ) 
                     == new_adjacent_portals.end() )
                {
                    // Send not found event
                    removeTravel( portal->getLocation() );
                    printf("Leaving portal '%s'\n", portal->getLocation().c_str());
                }
            }

            adjacent_portals = new_adjacent_portals;
        }
    }

    std::vector< Character* > adjacent_characters; 
    void Character::checkNPCs( std::vector< Character > *characters )
    {
        if ( characters->size() > 0 )
        {
            // Check for entering npc range
            std::vector< Character* > new_adjacent_characters = getAdjacentNPCs(characters);
            for ( Character* character : new_adjacent_characters )
            {
                // if a new character not found in adjacent_characters
                if ( std::find( adjacent_characters.begin(), adjacent_characters.end(), character ) 
                     == adjacent_characters.end() )
                {
                    // Send found event
                    spawnDialog( character->getAction(), character->getCenterX(), character->getCenterY() );
                    printf("Entering npc '%s'\n", character->getName().c_str());
                }
            }

            // Check for leaving npc range
            for ( Character* character : adjacent_characters )
            {
                // if an old character not found in new_adjacent_characters
                if ( std::find( new_adjacent_characters.begin(), new_adjacent_characters.end(), character ) 
                     == new_adjacent_characters.end() )
                {
                    // Send not found event
                    removeDialog( character->getAction() );
                    printf("Leaving npc '%s'\n", character->getName().c_str());
                }
            }

            adjacent_characters = new_adjacent_characters;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//            if ( !UIManager::inUI(UI::DIALOG) )     // If not in dialog already, check nearby npcs for focus
//            {
//                // Check if near any NPC's with dialog
//                focused_character = getAdjacentNPC(characters);
//                if ( focused_character != NULL )
//                {
//                    sendEvent( EventType::DIALOG, UI::DIALOG, focused_character->getAction(), 1,
//                               focused_character->getCenterX(), focused_character->getCenterY() );
//                }
//            }
//            else if ( focused_character != NULL )   // If in dialog, and npc has focus, check if still inside range
//            {
//                unsigned int distance = getDistance(focused_character->getCenterX(), 
//                                           focused_character->getCenterY(), DISTANCE_FAST );
//                if ( distance > focused_character->getVoiceDistance()) // Out of range
//                { 
//                    sendEvent( EventType::DIALOG, UI::DIALOG, focused_character->getAction(), 0 );
//                    focused_character = NULL;
//                }
//            }
//            else
//            {
//                printf("Where am I? Ahhh! -- character.cpp -> checkNPCs()\n");
//            }
        }
    }

    std::vector< Character* > Character::getAdjacentNPCs( std::vector< Character > *characters )
    {
        std::vector< Character* > adjacent_characters;
        for ( unsigned int i = 0; i < characters->size(); i++ )
        {
            Character* character = &(*characters)[i];
            if ( character->hasDialog() )
            {
                unsigned int distance_from_npc = character->getDistance(getCenterX(), getCenterY(), DISTANCE_FAST);
                if ( distance_from_npc <= character->getVoiceDistance() )
                {
                    adjacent_characters.push_back( character );
                }
            }
        }
        return adjacent_characters;
    }

    unsigned int Character::getDistance( int center_x, int center_y, Distance_Algorithm alg )
    {
        unsigned int distance = 0;
        if (alg == DISTANCE_FAST)
        {
            int distance_x = abs(getCenterX() - center_x);
            int distance_y = abs(getCenterY() - center_y);
            distance = distance_x + distance_y;
        }
        if (alg == DISTANCE_ACCURATE)
        {
            distance = 0;
            printf("Unimplemented DISTANCE_ACCURATE");
        }
        return distance; 
    }

    void Character::spawnTravel( std::string action )
    {
        sendEvent( EventType::TRAVEL, action, 1, {});
    }

    void Character::transitionTravel( std::string action )
    {
        std::unordered_map< std::string, int > properties = { { "pop", 1 } };
        sendEvent( EventType::TRAVEL, action, 1, properties );
    }

    void Character::removeTravel( std::string action )
    {
        sendEvent( EventType::TRAVEL, action, 0, {} );
    }

    void Character::spawnDialog( std::string action, int x, int y )
    {
        sendEvent( EventType::DIALOG, action, 1, x, y, {} );
    }

    void Character::transitionDialog( std::string action, int x, int y )
    {
        std::unordered_map< std::string, int > properties = { { "transition", 1 } };
        sendEvent( EventType::DIALOG, action, 1, x, y, properties );
    }

    void Character::removeDialog( std::string action )
    {
        sendEvent( EventType::DIALOG, action, 0, {} );
    }


    void Character::sendEvent( EventType type, std::string action, int value, std::unordered_map< std::string, int > properties = {} )
    {
        Event event = Event( type, action, value, properties );
        if ( UIManager::handleEvent( &event ) == false )
        {
            printf("character.cpp -> sendEvent() failed...\n");
        }
        
    }

    void Character::sendEvent( EventType type, std::string action, int value, int emit_x, int emit_y, std::unordered_map< std::string, int > properties = {} )
    {
        Event event = Event( type, action, value, emit_x, emit_y, properties);
        if ( UIManager::handleEvent( &event ) == false )
        {
            printf("character.cpp -> sendEvent() failed...\n");
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

//    Character* Character::getAdjacentNPC( std::vector< Character > *characters )
//    {
//        //TODO: Make pushDialog/pushMenu push copy of dialog/menu so that more than one of them can appear.
//        //      Also see if you can make the Font_Textures static, so that they don't have to be created
//        //      everytime a new dialog/menu is created
//        Character *closest_character = NULL;
//        unsigned int closest_distance = 10000; // start at some crazy high number
//        for ( unsigned int i = 0; i < characters->size(); i++ )
//        {
//            if ( (*characters)[i].hasDialog() )
//            {
//                unsigned int distance_from_npc = (*characters)[i].getDistance(getCenterX(), getCenterY(), DISTANCE_FAST);
//                if ( distance_from_npc < closest_distance && distance_from_npc <= (*characters)[i].getVoiceDistance() )
//                {
//                    closest_character = &((*characters)[i]);
//                }
//            }
//        }
//         
//        return closest_character;
//    }


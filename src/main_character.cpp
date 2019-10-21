#include "main_character.hpp"

#include <vector>
#include <algorithm>
#include "world.hpp"
#include "solid.hpp"
#include "character.hpp"

namespace game
{
    MainCharacter::MainCharacter()
        : DynamicCharacter( )
    {

    }
    
    MainCharacter::MainCharacter( SDL_Rect hitbox, SDL_Color color, std::string name )
        : DynamicCharacter( hitbox, color, name )
    {

    }

    std::vector< Solid* > adjacent_portals; 
    void MainCharacter::checkPortals( std::vector< Solid > *portals )
    {
        if ( portals->size() > 0 )
        {
            // Get all portals that character is inside of  
            std::vector< Solid* > new_adjacent_portals;
            for ( auto& portal : *portals)
            {
                if ( isInside( portal.getRekt() ) )
                {
                    new_adjacent_portals.push_back(&portal);
                }
            }

            // Check for entering portal range
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
    void MainCharacter::checkNPCs( std::vector< Character > *characters )
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

    std::vector< Character* > MainCharacter::getAdjacentNPCs( std::vector< Character > *characters )
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

    void MainCharacter::render( SDL_Renderer *renderer )
    {
        DynamicCharacter::render( renderer );
    }

    void MainCharacter::update()
    {
        DynamicCharacter::update();
        std::vector< Solid > *portals = World::getPortals();
        std::vector< Character > *characters = World::getCharactersInMap();

        // Check if inside Portals
        checkPortals(portals);

        // NPC dialog checks
        checkNPCs(characters);
    }
};

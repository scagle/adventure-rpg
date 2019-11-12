#include "main_character.hpp"

#include "world.hpp"

#include "globals.hpp"

#include <vector>
#include <algorithm>

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
                    Character::spawnTravel( portal->getLocation() );
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
                    Character::removeTravel( portal->getLocation() );
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
                    Character::spawnDialog( character->getAction() );
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
                    Character::removeDialog( character->getAction() );
                    printf("Leaving npc '%s'\n", character->getName().c_str());
                }
            }

            adjacent_characters = new_adjacent_characters;
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
                unsigned int distance_from_npc = character->getDistance(getCenterX(), 
                                                                        getCenterY(), 
                                                                        Solid::Distance_Algorithm::DISTANCE_FAST);
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
        std::vector< Solid > *solids = World::getSolids();
        std::vector< Solid > *portals = World::getPortals();
        std::vector< Character > *characters = World::getCharactersInMap();

        // Move Character
        DynamicCharacter::moveCharacter(&actual_x, &velocity_x, &(hitbox.x), &(hitbox.w), solids, SCREEN_WIDTH);
        DynamicCharacter::moveCharacter(&actual_y, &velocity_y, &(hitbox.y), &(hitbox.h), solids, SCREEN_HEIGHT);
        // Check if inside Portals
        checkPortals(portals);

        // NPC dialog checks
        checkNPCs(characters);
    }
};

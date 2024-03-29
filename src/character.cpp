#include "character.hpp"

#include "ui_manager.hpp"
#include "event.hpp"

#include "enums/event_type.hpp"

#include <algorithm>
#include <SDL.h>

namespace game
{

    Character::Character()
        : Solid( )
    {

    }

    Character::Character( SDL_Rect hitbox, SDL_Color color, std::string name )
        : Solid( hitbox, color ) 
    {
        construct(name, "");
    }

    Character::Character( SDL_Rect hitbox, SDL_Color color, std::string name, std::string action )
        : Solid( hitbox, color ) 
    {
        construct(name, action);
    }

    void Character::construct( std::string name, std::string action )
    {
        this->name = name; 
        this->action = action; 
    }

    void Character::spawnTravel( std::string action )
    {
        sendEvent( EventType::TRAVEL, action, 1, nullptr );
    }

    void Character::transitionTravel( std::string action )
    {
        std::unordered_map< std::string, int > properties = { { "pop", 1 } };
        sendEvent( EventType::TRAVEL, action, 1, nullptr );
    }

    void Character::removeTravel( std::string action )
    {
        sendEvent( EventType::TRAVEL, action, 0, nullptr );
    }

    void Character::spawnDialog( Character* npc, std::string action )
    {
        sendEvent( EventType::DIALOG, action, 1, npc );
    }

    void Character::transitionDialog( std::string action )
    {
        std::unordered_map< std::string, int > properties = { { "transition", 1 } };
        sendEvent( EventType::DIALOG, action, 1, nullptr );
    }

    void Character::removeDialog( std::string action )
    {
        sendEvent( EventType::DIALOG, action, 0, nullptr );
    }

    void Character::sendEvent( EventType type, std::string action, int value, Character* character )
    {
        Event event;
        if ( character == nullptr )
            event = Event( type, action, value );
        else
            event = Event( type, action, value, character );

        if ( UIManager::handleEvent( &event ) == false )
        {
            printf("character.cpp -> sendEvent() failed...\n");
        }
    }

    void Character::render( SDL_Renderer *renderer )
    {
        Solid::render( renderer );
    }

    void Character::update()
    {
        // Update solid-part of character
        Solid::update();
    }
};

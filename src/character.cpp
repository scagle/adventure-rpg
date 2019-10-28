#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <SDL.h>
#include <cstdlib>
#include <algorithm>

#include "character.hpp"
#include "solid.hpp"
#include "ui_manager.hpp"
#include "dialog_handler.hpp"
#include "travel_handler.hpp"
#include "globals.hpp"
#include "enums/event_type.hpp"

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
        sendEvent( EventType::TRAVEL, action, 1, this );
    }

    void Character::transitionTravel( std::string action )
    {
        std::unordered_map< std::string, int > properties = { { "pop", 1 } };
        sendEvent( EventType::TRAVEL, action, 1, this );
    }

    void Character::removeTravel( std::string action )
    {
        sendEvent( EventType::TRAVEL, action, 0, this );
    }

    void Character::spawnDialog( std::string action )
    {
        sendEvent( EventType::DIALOG, action, 1, this );
    }

    void Character::transitionDialog( std::string action )
    {
        std::unordered_map< std::string, int > properties = { { "transition", 1 } };
        sendEvent( EventType::DIALOG, action, 1, this );
    }

    void Character::removeDialog( std::string action )
    {
        sendEvent( EventType::DIALOG, action, 0, this );
    }

    void Character::sendEvent( EventType type, std::string action, int value, Character* character )
    {
        Event event = Event( type, action, value, character );
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
        Solid::update();
    }
};

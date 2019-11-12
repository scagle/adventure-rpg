#include "event.hpp"

#include "character.hpp"

#include "enums/event_type.hpp"

#include <string>

//! TODO: Make Proper Properties (no pun intended)

namespace game
{
    Event::Event()
        : type(EventType::UNKNOWN), id(""), value(0), character(nullptr) 
    {
        construct( nullptr );
    }

    Event::Event( EventType type, std::string id, int value ) 
        : type(type), id(id), value(value), character(nullptr) 
    {
        construct( nullptr );
    }

    // IE: Have dialog follow/hover over character
    Event::Event( EventType type, std::string id, int value, Character* c ) 
        : type(type), id(id), value(value), character(c) 
    { 
        construct( c );
    }

    // IE: Have dialog at specific position
    Event::Event( EventType type, std::string id, int value, int emit_x, int emit_y ) 
    {
        this->emit_x = emit_x;
        this->emit_y = emit_y;
    }

    void Event::construct( Character* )
    {
        if ( character == nullptr )
        {
            this->emit_x = 0;
            this->emit_y = 0;
        }
        else
        {
            this->emit_x = character->getEmitX();
            this->emit_y = character->getEmitY();
        }
    }
};

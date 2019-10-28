#include <unordered_map>
#include "event.hpp"
#include "character.hpp"
#include "enums/event_type.hpp"

//! TODO: Make Proper Properties (no pun intended)

namespace game
{
    Event::Event()
        : type(EventType::UNKNOWN), id(""), value(0), charactor(nullptr) 
    {
        construct( nullptr );
    }

    Event::Event( EventType t, std::string id, int v ) 
        : type(t), id(id), value(v), charactor(nullptr) 
    {
        construct( nullptr );
    }

    // IE: Have dialog follow/hover over character
    Event::Event( EventType type, std::string id, int value, Character* c ) 
        : type(t), id(id), value(v), charactor(c) 
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

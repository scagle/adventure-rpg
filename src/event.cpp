#include <unordered_map>
#include "event.hpp"
#include "enums/event_type.hpp"

namespace game
{
    Event::Event()
    {
        construct( EventType::UNKNOWN, "", 0, 0, 0, false );
    }

    Event::Event( EventType type )
    {
        construct( EventType::UNKNOWN, "", 0, 0, 0, false );
    }

    Event::Event( EventType type, std::string id ) 
    { 
        construct( EventType::UNKNOWN, id, 0, 0, 0, false );
    }

    Event::Event( EventType type, std::string id, int value ) 
    { 
        construct( EventType::UNKNOWN, id, value, 0, 0, false );
    }

    Event::Event( EventType type, std::string id, int value, int emit_x, int emit_y  ) 
    { 
        construct( EventType::UNKNOWN, id, value, emit_x, emit_y, true );
    }

    void Event::construct( EventType type, std::string id, int value, 
                           int emit_x, int emit_y, bool is_emitted )
    {
        this->type = type;
        this->id = id;
        this->value = value;
        this->emit_x = emit_x;
        this->emit_y = emit_y;
        this->is_emitted = is_emitted;
    }
};

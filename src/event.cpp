#include <unordered_map>
#include "event.hpp"
#include "enums/event_type.hpp"

namespace game
{
    Event::Event()
    {
        construct( EventType::UNKNOWN, "", 0 );
    }

    Event::Event( EventType type )
    {
        construct( EventType::UNKNOWN, "", 0 );
    }

    Event::Event( EventType type, std::string id ) 
    { 
        construct( EventType::UNKNOWN, id, 0 );
    }

    Event::Event( EventType type, std::string id, int value ) 
    { 
        construct( EventType::UNKNOWN, id, value );
    }

    void Event::construct( EventType type, std::string id, int value )
    {
        this->type = type;
        this->id = id;
        this->value = value;
    }
}

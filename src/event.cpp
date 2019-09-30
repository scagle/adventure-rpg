#include <unordered_map>
#include "event.hpp"
#include "enums/event_type.hpp"

namespace game
{
    Event::Event()
    {
        construct( EventType::UNKOWN, "", 0 );
    }

    Event::Event( EventType type )
    {
        construct( type, "", 0 );
    }

    Event::Event( EventType type, std::string id ) 
    { 
        construct( EventType::UNKOWN, id, 0 );
    }

    Event::Event( EventType type, std::string id, int value ) 
    { 
        construct( EventType::UNKOWN, id, value );
    }

    void Event::construct( EventType type, std::string id, int value )
    {
        this->type = type;
        this->id = id;
        this->value = value;
    }
}

#include <unordered_map>
#include "event.hpp"

namespace game
{
    // Static Declarations
    std::unordered_map< Event::Game_EventType, std::string > Event::type_to_names = {
        { Event::Game_EventType::PORTAL, "portal" },   // type, event_tracker_index
    };
    std::unordered_map< Event::Game_EventType, int > Event::type_to_indices = {
        { Event::Game_EventType::PORTAL, 0},
    };
    std::bitset< 255 > Event::event_tracker;

    Event::Event()
    {
        event_tracker.reset();
    }

    Event::Event( Game_EventType t, std::string v ) : type(t), value(v) 
    { 
        event_tracker.reset();
    }
}

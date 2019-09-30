#pragma once
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>
#include "enums/event_type.hpp"
#include "enums/ui.hpp"

namespace game
{
    class Event
    {
        public:
            EventType type;
            std::string id = "";
            int value = 0;

            Event();
            Event( EventType type );
            Event( EventType type, std::string id );
            Event( EventType type, std::string id, int value);
            virtual ~Event() { }

            void construct( EventType type, std::string id, int value );
    };
}

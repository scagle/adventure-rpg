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
            int emit_x = 0;  // x coordinate to display dialogs above entities
            int emit_y = 0;  // y coordinate to display dialogs above entities
            bool is_emitted = false;  // true if called using emit constructor(s)
            std::unordered_map< std::string, int> properties;

            Event();
            Event( EventType type );
            Event( EventType type, std::string id );
            Event( EventType type, std::string id, int value, std::unordered_map< std::string, int> );
            Event( EventType type, std::string id, int value, int emit_x, int emit_y, std::unordered_map< std::string, int> );
            virtual ~Event() { }
            void construct( EventType type, std::string id, int value, 
                            int emit_x, int emit_y, bool is_emitted,
                            std::unordered_map< std::string, int> properties);

            EventType getType() { return this->type; }
            std::string getID() { return this->id; }
            int getValue() { return this->value; }
            int getX() { return this->emit_x; }
            int getY() { return this->emit_y; }
            int isEmitted() { return (this->is_emitted); }
    };
};

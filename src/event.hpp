#pragma once
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>
#include "character.hpp"
#include "enums/event_type.hpp"
#include "enums/ui.hpp"

namespace game
{
    class Character;
    class Event
    {
        public:
            EventType type;
            std::string id = "";
            int value = 0;
            Character* character;
            int emit_x = 0;          // x coordinate to display dialogs above entities
            int emit_y = 0;          // y coordinate to display dialogs above entities
            bool is_emitted = true;  // "is an event that spawns an emitted container"

            Event( );
            Event( EventType t, std::string id, int v );
            Event( EventType type, std::string id, int value, Character* c );           // IE: Have dialog follow/hover over character
            Event( EventType type, std::string id, int value, int emit_x, int emit_y ); // IE: Have dialog at specific position
            virtual ~Event() { }
            void construct( Character* );

            EventType getType() { return this->type; }
            std::string getID() { return this->id; }
            int getValue() { return this->value; }
            int getX() { return this->emit_x; }
            int getY() { return this->emit_y; }
            Character* getCharacter() { return this->character; }
            bool isEmitted() { return this->is_emitted; }
    };
};

#pragma once
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>


namespace game
{
    class Event
    {
        public:
        enum class Game_EventType
        {
            PORTAL = 0,
            DIALOG = 1,
        };

        private:
            static std::unordered_map< Game_EventType, std::string > type_to_names;
            static std::unordered_map< Game_EventType, int > type_to_indices;
            static std::bitset< 255 > event_tracker;
            Game_EventType type;
            std::string value;

        public:
            Event();
            Event( Game_EventType t, std::string v );
            ~Event() { }
            Game_EventType getType() { return type; }
            std::string getValue() { return value; }
            std::string getName() { return type_to_names[type]; }
            static int getIndex(Game_EventType type) { return type_to_indices[type]; }
            static void setEvent(Game_EventType type, bool b) { event_tracker[getIndex(type)] = b; }
            static bool inEvent(Game_EventType type) { return event_tracker[getIndex(type)]; }
    };
}

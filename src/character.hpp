#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "solid.hpp" 
#include "enums/event_type.hpp" 

namespace game
{
    class Solid;

    class Character : public Solid
    {
        private:
        std::string name;
        bool main_character;
        std::string action;
        int voice_distance = 100;  // How far they can project their voice 

        public:
        Character();
        Character( SDL_Rect, SDL_Color, std::string );
        Character( SDL_Rect, SDL_Color, std::string, std::string );
        void construct( std::string, std::string ); // constructor wrapper

        bool hasDialog() { return (action != ""); }
        std::string getAction() { return this->action; }
        std::string getName() { return this->name; }

        // For positioning Emitted Floating dialogs ONLY
        int getEmitX() { return Solid::getCenterTopX(); } // Wrapper to make it more clear
        int getEmitY() { return Solid::getCenterTopY(); } // Wrapper to make it more clear

        unsigned int getVoiceDistance() { return this->voice_distance; }

        void spawnTravel      ( std::string action );
        void transitionTravel ( std::string action );
        void removeTravel     ( std::string action );
        void spawnDialog      ( std::string action );
        void transitionDialog ( std::string action );
        void removeDialog     ( std::string action );
        void sendEvent        ( EventType type, std::string action, int value, Character* );

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

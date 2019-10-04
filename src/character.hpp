#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "solid.hpp" 

namespace game
{
    class Character : public Solid
    {
        public:
        enum Distance_Algorithm
        {
            DISTANCE_FAST = 0,
            DISTANCE_ACCURATE = 1,
        };

        private:
        float actual_x; 
        float actual_y;
        float velocity_x;
        float velocity_y;
        std::string name;
        bool main_character;
        std::string action;
        Solid *focused_portal = NULL;
        Character *focused_character = NULL;
        int voice_distance = 100;  // How far they can project their voice 

        public:
        Character();
        Character( SDL_Rect, SDL_Color, std::string );
        Character( SDL_Rect, SDL_Color, std::string, bool );
        Character( SDL_Rect, SDL_Color, std::string, bool, std::string );
        void construct( SDL_Rect, SDL_Color, std::string, bool, std::string ); // constructor wrapper

        bool moveCharacter( float *, float *, int *, int *, std::vector< Solid > *, int );
        void checkPortals( std::vector< Solid > * );
        void checkNPCs( std::vector< Character > * );
        Character* getAdjacentNPC( std::vector< Character > * );
        bool hasDialog() { return (action != ""); }
        std::string getAction() { return this->action; }
        unsigned int getDistance( float, float, Distance_Algorithm );
        unsigned int getCenterX() { return this->hitbox.x + this->hitbox.w / 2; }
        unsigned int getCenterY() { return this->hitbox.y; }
        unsigned int getVoiceDistance() { return this->voice_distance; }
        void sendEvent(EventType type, UI ui, std::string action, int value);
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        // Accessors
        // Mutators
        void setVelocity( float vx, float vy ) { velocity_x = vx; velocity_y = vy; } 
            
    };
};

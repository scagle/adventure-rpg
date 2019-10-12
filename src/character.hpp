#pragma once
#include <vector>
#include <string>
#include <unordered_map>
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
        std::vector< Character* > getAdjacentNPCs( std::vector< Character > *characters );
        bool hasDialog() { return (action != ""); }
        std::string getAction() { return this->action; }
        std::string getName() { return this->name; }
        unsigned int getDistance( int, int, Distance_Algorithm );

        // For positioning floating dialogs only
        int getEmitX() { return this->hitbox.x + this->hitbox.w / 2; }
        int getEmitY() { return this->hitbox.y; }

        // Get Center X and Center Y
        int getCenterX() { return this->hitbox.x + this->hitbox.w / 2; }
        int getCenterY() { return this->hitbox.y + this->hitbox.h / 2; }

        unsigned int getVoiceDistance() { return this->voice_distance; }

        void spawnTravel( std::string action );         // Create a footer message
        void transitionTravel( std::string action );
        void removeTravel( std::string action );
        void spawnDialog( std::string action, int, int );
        void transitionDialog( std::string action, int, int );
        void removeDialog( std::string action );
        void sendEvent( EventType type, std::string action, int value, std::unordered_map< std::string, int > );
        void sendEvent( EventType type, std::string action, int value, int emit_x, int emit_y, std::unordered_map< std::string, int > );
        virtual void render( SDL_Renderer *renderer );
        virtual void update();

        void setVelocity( float vx, float vy ) { velocity_x = vx; velocity_y = vy; }
        void setPosition( Position* pos) override { this->actual_x = pos->x; this->actual_y = pos->y; }
            
    };
};

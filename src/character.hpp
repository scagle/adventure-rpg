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

        public:
        Character();
        Character( SDL_Rect, SDL_Color, std::string );
        Character( SDL_Rect, SDL_Color, std::string, bool );
        Character( SDL_Rect, SDL_Color, std::string, bool, std::string );
        void construct( SDL_Rect, SDL_Color, std::string, bool, std::string ); // constructor wrapper

        bool moveCharacter( float *, float *, int *, int *, std::vector< Solid > *, int );
        void checkPortal( std::vector< Solid > * );
        void checkNearby( std::vector< Character > * );
        bool hasDialog() { return (action != ""); }
        std::string getAction() { return this->action; }
        unsigned int getDistance( float, float, Distance_Algorithm );
        unsigned int getCenterX() { return this->hitbox.x + this->hitbox.w / 2; }
        unsigned int getCenterY() { return this->hitbox.y; }
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        // Accessors
        // Mutators
        void setVelocity( float vx, float vy ) { velocity_x = vx; velocity_y = vy; } 
    };
};

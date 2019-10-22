#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "solid.hpp" 
#include "character.hpp" 

namespace game
{
    class MainCharacter;

    // Moveable/Animated Character ( Collidable or not )
    class DynamicCharacter : public Character
    {
        public:
        enum class Behavior
        {
            NONE,
            LOCAL_FOLLOW,
            GLOBAL_FOLLOW,
            LOCAL_FLEE,
            GLOBAL_FLEE,
        };

        protected:
        float actual_x; 
        float actual_y;
        float velocity_x;
        float velocity_y;
        Behavior behavior = Behavior::NONE; 
        unsigned int local_radius = 100;   // Radius of behavior
        double speed = 0.5;       

        public:
        DynamicCharacter();
        DynamicCharacter( SDL_Rect, SDL_Color, std::string );
        DynamicCharacter( SDL_Rect, SDL_Color, std::string, std::string);
        DynamicCharacter( SDL_Rect, SDL_Color, std::string, Behavior );
        DynamicCharacter( SDL_Rect, SDL_Color, std::string, std::string, Behavior );
        virtual ~DynamicCharacter() { }
        void construct( SDL_Rect hitbox );

        // Accessor / Mutators
        void setVelocity( float vx, float vy ) { velocity_x = vx; velocity_y = vy; }
        void setPosition( Position* pos) { this->actual_x = pos->x; this->actual_y = pos->y; }

        // Meaty methods
        bool moveCharacter( float *, float *, int *, int *, std::vector< Solid > *, int );
        void performBehavior( MainCharacter* ); 
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

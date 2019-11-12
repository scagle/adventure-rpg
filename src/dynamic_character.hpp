#pragma once

// Forward Declarations
namespace game
{
    class Solid;
    class MainCharacter;
}
class SDL_Rect;
class SDL_Color;
class SDL_Renderer;

#include "character.hpp" 
#include "datatypes/position.hpp" 

#include <vector>
#include <string>
#include <unordered_map>

namespace game
{
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
                LOCAL_RANDOM,
                RANDOM,
            };

        protected:
            float actual_x; 
            float actual_y;
            float velocity_x;
            float velocity_y;
            Behavior behavior = Behavior::NONE; 
            unsigned int detect_range = 100;        // Detect Circle diameter     ( IE: start following if within this range )
            unsigned int post_detect_range = 175;   // Outer-Most-Circle diameter ( IE: stop following if out of this range )
            unsigned int too_close_range = 40;      // Inner-Circle diameter      ( IE: stop following if within this range )
            bool following = false;
            bool fleeing = false;
            double speed = 0.4;       

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

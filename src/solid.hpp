#pragma once
// Forward Declaration inside game
namespace game
{
    class Event;
};

#include <string>
#include <SDL.h>
#include <stdint.h>

namespace game
{
    class Solid
    {
        public:
            enum class Distance_Algorithm
            {
                DISTANCE_FAST = 0,
                DISTANCE_ACCURATE = 1,
            };

            enum class Type { 
                SOLID,
                PORTAL,        
            };

        // Could be privatized, but for accessibility, I want to access these 
        // directly in inherited classes
        protected:
            uint32_t portal_color = 0;
            SDL_Rect hitbox;
            SDL_Color color;
            Type type = Type::SOLID;                 // type(s) (bit addressing) of solid 
            std::string location = ""; // map to jump to if main character is 100% inside this solid (PORTAL's only!)

        public:
            // Global Public Variables
            // Constructors
            Solid();
            Solid(SDL_Rect h, SDL_Color c);
            Solid(SDL_Rect h, SDL_Color c, Type t);
            Solid(SDL_Rect h, SDL_Color c, Type t, std::string l);

            // Basic Accessors
            SDL_Rect* getRekt() { return &hitbox; }
            SDL_Color* getColor() { return &color; }
            Type getType() { return this->type; }
            std::string getLocation() { return this->location; }
            int getCenterX() { return this->hitbox.x + this->hitbox.w / 2; }
            int getCenterY() { return this->hitbox.y + this->hitbox.h / 2; }
            int getCenterTopX() { return this->hitbox.x + this->hitbox.w / 2; }
            int getCenterTopY() { return this->hitbox.y; }
            uint32_t getColorNumber() { return ( (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b) ); }

            // Meaty Methods
            bool isInside( SDL_Rect* ); // Check if inside another solid
            unsigned int getDistance( int, int, Distance_Algorithm );
            virtual void render( SDL_Renderer *renderer );
            virtual void update();
    };
};

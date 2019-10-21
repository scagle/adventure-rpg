#pragma once

#include <string>
#include <SDL.h>
#include <stdint.h>
#include "event.hpp"
#include "datatypes/position.hpp"

namespace game
{
    class Solid
    {
        private:
        uint32_t portal_color = 0;

        public:
        /*! TODO: Privatize the variables somehow
         *  \todo Privatize the variables somehow
         */

        enum Distance_Algorithm
        {
            DISTANCE_FAST = 0,
            DISTANCE_ACCURATE = 1,
        };

        enum class Type { 
            SOLID,
            PORTAL,        
        };

        // Global Public Variables
        SDL_Rect hitbox;
        SDL_Color color;
        Type type;             // type(s) (bit addressing) of solid 
        std::string location; // map to jump to if main character is 100% inside this solid (PORTAL's only!)

        // Constructors
        Solid() : type(Type::SOLID) { }
        Solid(Type t) : type(t) { }
        Solid(SDL_Rect h, SDL_Color c, Type t) : hitbox(h), color(c), type(t) { }
        Solid(SDL_Rect h, SDL_Color c, Type t, std::string l) : hitbox(h), color(c), type(t), location(l) { }

        // Basic Accessors
        SDL_Rect* getRekt() { return &hitbox; }
        SDL_Color* getColor() { return &color; }
        Type getType() { return this->type; }
        std::string getLocation() { return this->location; }
        int getCenterX() { return this->hitbox.x + this->hitbox.w / 2; }
        int getCenterY() { return this->hitbox.y + this->hitbox.h / 2; }
        uint32_t getColorNumber() { return ( (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b) ); }

        // Meaty Methods
        bool isInside( SDL_Rect* ); // Check if inside another solid
        unsigned int getDistance( int, int, Distance_Algorithm );
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

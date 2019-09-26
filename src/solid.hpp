#pragma once

#include <string>
#include <SDL.h>
#include <stdint.h>
#include "event.hpp"

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
        enum class Type { 
            SOLID,
            PORTAL,        
        };

        SDL_Rect hitbox;
        SDL_Color color;
        Type type;             // type(s) (bit addressing) of solid 
        std::string location; // map to jump to if main character is 100% inside this solid (PORTAL's only!)


        Solid() : type(Type::SOLID) { }
        Solid(Type t) : type(t) { }
        Solid(SDL_Rect h, SDL_Color c, Type t) : hitbox(h), color(c), type(t) { }
        Solid(SDL_Rect h, SDL_Color c, Type t, std::string l) : hitbox(h), color(c), type(t), location(l) { }

        SDL_Rect* getRekt() { return &hitbox; }
        SDL_Color* getColor() { return &color; }
        uint32_t getColorNumber() { return ( (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b) ); }
        virtual void render( SDL_Renderer *renderer );
        virtual void update();

        // Check if this solid is close to another solid 
        bool isInside( SDL_Rect* ); 
        Type getType() { return this->type; }
        std::string getLocation() { return this->location; }
    };
}

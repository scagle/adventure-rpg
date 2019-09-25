#pragma once

#include <stdint.h>
#include <SDL.h>

namespace game
{
    class Solid
    {
        private:

        public:
        /*! TODO: Privatize the variables somehow
         *  \todo Privatize the variables somehow
         */
        SDL_Rect hitbox;
        SDL_Color color;
        Solid();

        Solid(SDL_Rect hitbox, SDL_Color color) { this->hitbox = hitbox; this->color = color; }
        SDL_Rect* getRekt() { return &hitbox; }
        SDL_Color* getColor() { return &color; }
        uint32_t getColorNumber() { return ( (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b) ); }
        virtual void render( SDL_Renderer *renderer );
    };
}

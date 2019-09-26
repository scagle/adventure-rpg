#include <SDL.h>
#include <stdlib.h>
#include "solid.hpp"

namespace game
{
    void Solid::render( SDL_Renderer *renderer )
    {
        if (type == Type::PORTAL)
        {
            SDL_SetRenderDrawColor( renderer, 
                    (portal_color & 0x00FF0000) >> 16, 
                    (portal_color & 0x0000FF00) >>  8, 
                    (portal_color & 0x000000FF) >>  0, 
                    50 );
        }
        else
        {
            SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        }
        SDL_RenderFillRect( renderer, &hitbox );
    }

    void Solid::update()
    {
        if (type == Type::PORTAL)
        {
            portal_color = portal_color + 5; 
            portal_color &= 0x00FFFFFFF;
        }
    }

    bool Solid::isInside( SDL_Rect* box)
    {
        if ( hitbox.x >= box->x &&
             hitbox.y >= box->y &&
             hitbox.x + hitbox.w <= box->x + box->w &&
             hitbox.y + hitbox.h <= box->y + box->h )
            return true;
        return false;
    }
}


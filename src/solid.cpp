#include <SDL.h>
#include <stdlib.h>
#include "solid.hpp"

namespace game
{

    Solid::Solid() { }
    Solid::Solid(SDL_Rect h, SDL_Color c)                        : hitbox(h), color(c)                       { }
    Solid::Solid(SDL_Rect h, SDL_Color c, Type t)                : hitbox(h), color(c), type(t)              { }
    Solid::Solid(SDL_Rect h, SDL_Color c, Type t, std::string l) : hitbox(h), color(c), type(t), location(l) { }

    bool Solid::isInside( SDL_Rect* box)
    {
        if ( hitbox.x >= box->x &&
             hitbox.y >= box->y &&
             hitbox.x + hitbox.w <= box->x + box->w &&
             hitbox.y + hitbox.h <= box->y + box->h )
        {
            return true;
        }
        return false;
    }

    unsigned int Solid::getDistance( int center_x, int center_y, Distance_Algorithm alg )
    {
        unsigned int distance = 0;
        if (alg == DISTANCE_FAST)
        {
            int distance_x = abs(getCenterX() - center_x);
            int distance_y = abs(getCenterY() - center_y);
            distance = distance_x + distance_y;
        }
        if (alg == DISTANCE_ACCURATE)
        {
            distance = 0;
            printf("Unimplemented DISTANCE_ACCURATE");
        }
        return distance; 
    }

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

};

#include <SDL.h>
#include "solid.hpp"

namespace game
{
    Solid::Solid()
    {

    }
    void Solid::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &hitbox );
    }
}

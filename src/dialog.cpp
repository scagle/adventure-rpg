#include <SDL.h>
#include "dialog.hpp"

namespace game
{
    void Dialog::setAnchor( int entity_center_x, int entity_center_y )
    {
        this->box = {0, 0, 200, 50};
    }

    void Dialog::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
        SDL_RenderFillRect( renderer, &box );
    }

    void Dialog::update()
    {

    }
};

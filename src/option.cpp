#include <SDL.h>
#include <string>
#include "option.hpp"

namespace game
{
    void Option::render( SDL_Renderer *renderer, SDL_Rect *menu_box, int height, int index )
    {
        SDL_Rect option_box = { menu_box->x + 30, 
                                menu_box->y + 30 + height * index,  
                                menu_box->w - 60, 
                                height 
        };
        SDL_SetRenderDrawColor( renderer, 
                                OPTION_BACKGROUND_COLOR.r,
                                OPTION_BACKGROUND_COLOR.g,
                                OPTION_BACKGROUND_COLOR.b,
                                OPTION_BACKGROUND_COLOR.a
        );
        SDL_RenderFillRect( renderer, &option_box );
    }
}

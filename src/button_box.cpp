#include <SDL.h>
#include "button_box.hpp"
#include "text_box.hpp"

namespace ButtonBox
{
    ButtonBox::ButtonBox( std::string text, SDL_Texture *tt, SDL_Rect box, SDL_Color color, std::string action )
    {
        TextBox::construct(text, tt, box, color);
        this->action = action;
    }

    std::string getAction()
    {
        return this->action;
    }

    void ButtonBox::render( SDL_Renderer *renderer, SDL_Color *selected_color )
    {
        if (selected_color != NULL)  // If this button is selected, change color
            SDL_SetRenderDrawColor( renderer, selected_color->r, selected_color->g, selected_color->b, selected_color->a );
        else
            SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );

        SDL_RenderFillRect( renderer, &box );
        SDL_RenderCopy( renderer, text_texture, NULL, &box ); 
    }

    void ButtonBox::update()
    {

    }
};

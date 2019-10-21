#include <SDL.h>
#include "button_box.hpp"
#include "text_box.hpp"
#include "datatypes/properties.hpp"

namespace game
{
    ButtonBox::ButtonBox()
        : TextBox()
    {
        construct( "", {} );
    }

    ButtonBox::ButtonBox( std::string action, Properties p )
        : TextBox()
    {
        construct( action, p  );
    }

    ButtonBox::ButtonBox( std::string text, int font_index, std::string action, Properties p )
        : TextBox( text, font_index, p )
    {
        construct( action, p );
    }

    ButtonBox::ButtonBox( std::string text, int font_index, SDL_Color background, std::string action, Properties p )
        : TextBox( text, font_index, background, p )
    {
        construct( action, p );
    }

    void ButtonBox::construct( std::string action, Properties p )
    {
        this->action = action;
        this->properties = p;
    }

    void ButtonBox::render( SDL_Renderer *renderer, SDL_Rect *button_rect, bool selected )
    {
        if (selected) // If this button is selected, change color
        {
            SDL_Color sc = BUTTON_SELECTED_BACKGROUND_COLOR;
            SDL_SetRenderDrawColor( renderer, sc.r, sc.g, sc.b, sc.a );
        }
        else
        {
            SDL_SetRenderDrawColor( renderer, background.r, background.g, background.b, background.a );
        }

        SDL_RenderFillRect( renderer, button_rect );
        SDL_RenderCopy( renderer, text_texture, NULL, button_rect ); 
    }

    void ButtonBox::update()
    {

    }
};

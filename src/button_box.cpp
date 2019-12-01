#include "button_box.hpp"

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
            text_texture.setBackground( BUTTON_SELECTED_BACKGROUND_COLOR );
        }
        else
        {
            text_texture.setBackground( background );
        }

        text_texture.render( renderer, text, button_rect, align );
    }

    void ButtonBox::update()
    {

    }
};


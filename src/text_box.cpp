#include "text_box.hpp"

namespace game
{
    TextBox::TextBox()
    {
        construct( "", NULL, {0, 0, 100, 100}, {0, 0, 0, 255} );
    }

    TextBox::TextBox( std::string text, SDL_Texture *tt, SDL_Rect box )
    {
        construct( text, tt, box, {0, 0, 0, 255} );
    }

    TextBox::TextBox( std::string text, SDL_Texture *tt, SDL_Rect box, SDL_Color color )
    {
        construct( text, tt, box, color );
    }

    void TextBox::construct( std::string text, SDL_Texture *tt, SDL_Rect box, SDL_Color color )
    {
        this->text = text;
        this->text_texture = tt;
        this->box = box;
        this->color = color;
    }

    void TextBox::render( SDL_Renderer *renderer )
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &box );
        SDL_RenderCopy( renderer, text_texture, NULL, &box ); 
    }

    void TextBox::update()
    {

    }
};

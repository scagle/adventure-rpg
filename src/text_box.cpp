#include "text_box.hpp"

#include "gamedata.hpp"

#include <SDL_ttf.h>

namespace game
{
    TextBox::TextBox()
    {
        construct( "", 0, {255, 255, 255, 255}, Properties() );
    }

    TextBox::TextBox( std::string text, int font_index, Properties p)
    {
        construct( text, font_index, {255, 255, 255, 255}, p );
    }

    TextBox::TextBox( std::string text, int font_index, SDL_Color background, Properties p )
    {
        construct( text, font_index, background, p );
    }

    void TextBox::construct( std::string text, int font_index, SDL_Color background, Properties p )
    {
        this->text = text;
        this->font_index = font_index;
        this->background = background;
        this->foreground = {0, 0, 0, 255};
        this->properties = p;
        initText();
    }

    void TextBox::render( SDL_Renderer *renderer, SDL_Rect *text_rect )
    {
        SDL_SetRenderDrawColor( renderer, background.r, background.g, background.b, background.a );
        SDL_RenderFillRect( renderer, text_rect );
        SDL_RenderCopy( renderer, text_texture, NULL, text_rect ); 
    }

    void TextBox::update()
    {

    }

    void TextBox::initText()
    {
        SDL_Renderer *renderer = GameData::getActiveRenderer();
        SDL_Surface *text_surface = TTF_RenderText_Solid( GameData::getFont(font_index), text.c_str(), foreground );
        text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
        SDL_FreeSurface(text_surface);
    }
};

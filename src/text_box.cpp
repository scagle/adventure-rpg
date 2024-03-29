#include "text_box.hpp"

#include "gamedata.hpp"
#include "game_texture.hpp"

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
        text_texture.render( renderer, text, text_rect, align );
    }

    void TextBox::update()
    {

    }

    void TextBox::initText()
    {
        //SDL_Renderer *renderer = GameData::getActiveRenderer();
        //TTF_Font *font = GameData::getFont(0);
        //text_texture.loadFromRenderedText( renderer, text, font, foreground );
    }
};

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "option.hpp"
#include "gamedata.hpp"

namespace game
{
    Option::Option( std::string t, std::string n ) 
        : text(t), next(n), background(OPTION_BACKGROUND_COLOR), foreground(OPTION_FOREGROUND_COLOR)
    { 
        font = GameData::getDefaultFont(0);
        initText();
    }

    Option::Option( std::string t, std::string n, SDL_Color bg, SDL_Color fg, int font_index) 
        : text(t), next(n), background(bg), foreground(fg)
    { 
        font = GameData::getDefaultFont(font_index);
        initText();
    }

    Option::~Option() 
    {
        SDL_DestroyTexture(message);
    }

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
        SDL_RenderCopy( renderer, message, NULL, &option_box ); 
    }
    
    void Option::initText()
    {
        SDL_Surface *text_surface = TTF_RenderText_Solid( font, text.c_str(), foreground );
        message = SDL_CreateTextureFromSurface( GameData::getActiveRenderer(), text_surface );
        SDL_FreeSurface(text_surface);
    }
}

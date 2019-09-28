#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <thread>
#include "option.hpp"
#include "gamedata.hpp"

namespace game
{
    Option::Option( std::string t, std::string n ) 
        : text(t), next(n), background(OPTION_BACKGROUND_COLOR), foreground(OPTION_FOREGROUND_COLOR), font_index(0)
    { 
        font = GameData::getFont(font_index);
        initText();
    }

    Option::Option( std::string t, std::string n, SDL_Color bg, SDL_Color fg, int fi ) 
        : text(t), next(n), background(bg), foreground(fg), font_index(fi)
    { 
        font = GameData::getFont(font_index);
        initText();
    }

    // Copy Constructor
    Option::Option(const Option &other) : text(other.text), next(other.next), 
        background(other.background), foreground(other.foreground)
    {
        font = GameData::getFont(other.font_index);
        initText(); // Initialize BRAND NEW texture, and DONT delete my other ones >:(
    }

    // Copy Assignment
    Option& Option::operator=(const Option &other)    
    {
        this->text = other.text;        // Text of option
        this->next = other.next;        // string of the next menu key (ie: "main", "save screen", etc)
        this->background = other.background;    // Background color of option
        this->foreground = other.foreground;    // Foreground color of option
        this->font = GameData::getFont(other.font_index);
        //void (Menu::*call_function)(); // function to call when activated
        initText(); // Initialize BRAND NEW texture, and DONT delete my other ones >:(

        return *this;
    }

    Option::~Option() 
    {
        SDL_DestroyTexture(message); // I'm watching you... 
    }

    void Option::render( SDL_Renderer *renderer, SDL_Rect *menu_box, int height, int index, bool selected )
    {
        SDL_Rect option_box = { menu_box->x + 30, 
                                menu_box->y + 30 + height * index,  
                                menu_box->w - 60, 
                                height 
        };
        if (selected)
            SDL_SetRenderDrawColor( renderer, 0, 100, 0, 255 );
        else
            SDL_SetRenderDrawColor( renderer, background.r, background.g, background.b, background.a );

        SDL_RenderFillRect( renderer, &option_box );
        SDL_RenderCopy( renderer, message, NULL, &option_box ); 
    }
    
    void Option::initText()
    {
        SDL_Renderer *renderer = GameData::getActiveRenderer();
        SDL_Surface *text_surface = TTF_RenderText_Solid( font, text.c_str(), foreground );
        message = SDL_CreateTextureFromSurface( renderer, text_surface );
        SDL_FreeSurface(text_surface);
    }
}

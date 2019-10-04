#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "globals.hpp"

class Menu;

namespace game
{
    class Option
    {
        /*! TODO: Implement dynamic options that allow for more than just clicking
         *  \todo Implement dynamic options that allow for more than just clicking
         */
        private:
            std::string text;        // Text of option
            std::string next;        // string of the next menu key (ie: "main", "save screen", etc)
            SDL_Color background;    // Background color of option
            SDL_Color foreground;    // Foreground color of option
            //void (Menu::*call_function)(); // function to call when activated
            TTF_Font *font;          // Font to draw text with
            SDL_Texture *message;    // Font texture to draw
            int font_index = 0;
            bool initialized_text = false;

        public:
            Option( std::string t, std::string n ) ;
            Option( std::string t, std::string n, SDL_Color bg, SDL_Color fg, int) ;
            Option(const Option &);
            Option& operator=(const Option &);   
            ~Option();

            virtual void render( SDL_Renderer*, SDL_Rect*, int, int, bool );
            void initText();
            std::string getText() { return this->text; }
            std::string getNext() { return this->next; }
            SDL_Color* getForeground() { return &(this->foreground); }
            SDL_Color* getBackground() { return &(this->background); }
            SDL_Texture* getTextMessage() { return this->message; }

    };
};

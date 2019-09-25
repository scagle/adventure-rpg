#pragma once
#include <SDL.h>
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

        public:
            Option( std::string t, std::string n ) 
                : text(t), next(n), background(OPTION_BACKGROUND_COLOR), foreground(OPTION_FOREGROUND_COLOR) { }

            Option( std::string t, std::string n, SDL_Color bg, SDL_Color fg ) 
                : text(t), next(n), background(bg), foreground(fg) { }

            virtual void render( SDL_Renderer*, SDL_Rect*, int, int );

    };
}

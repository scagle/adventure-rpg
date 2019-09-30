#pragma once
#include <SDL.h>
#include <string>
#include "text_box.hpp"
#include "globals.hpp"

namespace game
{
    class ButtonBox : public TextBox
    {
        private:
        std::string action;

        public:
        ButtonBox( );
        ButtonBox( std::string );
        ButtonBox( std::string, int, std::string );
        ButtonBox( std::string, int, SDL_Color, std::string );

        void construct( std::string );
        std::string getAction();
        virtual void render( SDL_Renderer *renderer, SDL_Rect *button_rect, bool selected );
        virtual void update();
    };
};

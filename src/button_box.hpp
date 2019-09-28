#pragma once
#include <SDL.h>
#include <string>
#include "text_box.hpp"

namespace game
{
    class ButtonBox : public TextBox
    {
        private:
        std::string action;

        public:
        ButtonBox( std::string, SDL_Texture*, SDL_Rect, SDL_Color, std::string );

        std::string getAction();
        virtual void render( SDL_Renderer *renderer, SDL_Color *selected_color );
        virtual void update();
    };
};

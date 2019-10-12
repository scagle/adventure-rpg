#pragma once
#include <SDL.h>
#include <string>
#include "text_box.hpp"
#include "globals.hpp"
#include "datatypes/properties.hpp"

namespace game
{
    class ButtonBox : public TextBox
    {
        private:
        std::string action;

        public:
        ButtonBox( );
        ButtonBox( std::string, Properties );
        ButtonBox( std::string, int, std::string, Properties );
        ButtonBox( std::string, int, SDL_Color, std::string, Properties );

        void construct( std::string, Properties );
        std::string getAction() { return this->action; } 
        virtual void render( SDL_Renderer *renderer, SDL_Rect *button_rect, bool selected );
        virtual void update();
    };
};

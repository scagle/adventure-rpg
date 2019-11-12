#pragma once

// Forward Declarations
namespace game
{
    class Properties;
};
class SDL_Color;
class SDL_Rect;
class SDL_Renderer;

#include "text_box.hpp"

#include "globals.hpp"

#include <string>

namespace game
{
    class Properties;

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

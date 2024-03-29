#pragma once

#include "datatypes/properties.hpp"
#include "game_texture.hpp"
#include "external/SDL_FontCache.h"

#include <string>
#include <SDL.h>

namespace game
{
    class TextBox  
    {
        protected:   // We want inherited classes to have access to members
            std::string text;
            GameTexture text_texture;
            FC_AlignEnum align = FC_ALIGN_CENTER;
            SDL_Color background;
            SDL_Color foreground;
            int font_index;
            Properties properties;

        public:
            TextBox();
            TextBox( std::string, int, Properties );
            TextBox( std::string, int, SDL_Color, Properties );
            virtual ~TextBox() { }

            void construct( std::string, int, SDL_Color, Properties );
            virtual Properties* getProperties() { return &(this->properties); } 
            virtual void render( SDL_Renderer *renderer, SDL_Rect *text_rect );
            virtual void update();
            virtual void initText();

    };
};

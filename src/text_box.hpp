#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace game
{
    class TextBox  
    {
        protected:   // We want inherited classes to have access to members
        std::string text;
        SDL_Texture *text_texture;
        SDL_Color background;
        SDL_Color foreground;
        int font_index;

        public:
        TextBox();
        TextBox( std::string, int );
        TextBox( std::string, int, SDL_Color );
        virtual ~TextBox() { }

        void construct( std::string, int, SDL_Color );
        virtual void render( SDL_Renderer *renderer, SDL_Rect *text_rect );
        virtual void update();
        virtual void initText();

    };
};

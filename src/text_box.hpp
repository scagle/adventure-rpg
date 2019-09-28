#pragma once
#include <SDL.h>
#include <string>

namespace game
{
    class TextBox  
    {
        private:
        std::string text;
        SDL_Texture *text_texture;
        SDL_Rect box;
        SDL_Color color;

        public:
        TextBox();
        TextBox( std::string, SDL_Texture*, SDL_Rect );
        TextBox( std::string, SDL_Texture*, SDL_Rect, SDL_Color );
        virtual ~TextBox() { }

        void construct( std::string, SDL_Texture*, SDL_Rect, SDL_Color );
        virtual void render( SDL_Renderer *renderer );
        virtual void update();

    };
};

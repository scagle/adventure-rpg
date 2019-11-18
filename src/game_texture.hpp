// This file was largely based on LazyFoo's rendition over at:
// https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php

#pragma once

#include <SDL.h> // Could forward declare individual bits and pieces, but not right now
#include <SDL_ttf.h>
#include <string>

namespace game
{
    class GameTexture
    {
        private:
            // Private Members
            SDL_Texture* texture = NULL;
            int width = 0;
            int height = 0;
            TTF_Font* font = NULL;
            bool background = true;
            SDL_Color background_color = { 255, 255, 255, 255 };

        public:
            GameTexture();
            GameTexture( int w, int h );
            GameTexture( int w, int h, int f );
            virtual ~GameTexture() { }


            // Load image from file at specified path
            bool loadFromFile( std::string path ); 

            // Create image image from font string
            bool loadFromRenderedText( SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color color );

            // Deallocate Texture
            void free(); 

            // Manipulate Background
            void setBackground( const SDL_Color& color );
            void setBackground( SDL_Color& color );
            void setBackground( unsigned char red, unsigned char green, unsigned char blue );
            void unsetBackground();

            // Set color modulation
            void setColor( const SDL_Color& color );
            void setColor( SDL_Color& color );
            void setColor( unsigned char red, unsigned char green, unsigned char blue );

            // Set blending
            void setBlendMode( SDL_BlendMode blending );

            // Set alpha modulation
            void setAlpha( unsigned char alpha );

            //Renders texture at given point
            void render( SDL_Renderer* renderer, SDL_Rect* rect, SDL_Rect* clip = NULL, double angle = 0.0, 
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );


            // Accessors
            int getWidth() { return this->width; };
            int getHeight() { return this->height; };

            // Mutators
    };
};;


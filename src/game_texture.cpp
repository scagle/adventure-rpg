#include "game_texture.hpp"

#include "gamedata.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace game
{
    // Static Declarations

    // Constructors
    GameTexture::GameTexture() { }
    GameTexture::GameTexture( int w, int h ) : width( w ), height( h ), font( GameData::getFont(0) ) { }
    GameTexture::GameTexture( int w, int h, int f ) : width( w ), height( h ), font( GameData::getFont(f) ) { }

    // Methods
    bool GameTexture::loadFromRenderedText( SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color color )
    {
        // Get rid of preexisting texture
        free();

        // Render text surface
        SDL_Surface* text_surface = TTF_RenderText_Solid( font, text.c_str(), color );
        if ( text_surface == nullptr )
        {
            printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        else
        {
            // Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface( renderer, text_surface );
            if ( texture == nullptr )
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                // Get image dimensions
                width = text_surface->w;
                height = text_surface->h;
            }

            // Get rid of old surface
            SDL_FreeSurface( text_surface );
        }

        // Return success
        return (texture != nullptr);
    }

    void GameTexture::free()
    {
        if ( texture != nullptr )
        {
            SDL_DestroyTexture( texture );
            texture = nullptr;
            width = 0;
            height = 0;
        }
    }

    void GameTexture::setBackground( const SDL_Color& color )
    {
        setBackground( color.r, color.g, color.b );
    }
        
    void GameTexture::setBackground( SDL_Color& color )
    {
        setBackground( color.r, color.g, color.b );
    }

    void GameTexture::setBackground( unsigned char red, unsigned char green, unsigned char blue )
    {
        background = true;
        background_color = { red, green, blue, 255 };
    }

    void GameTexture::unsetBackground()
    {
        background = false;
    }

    void GameTexture::setColor( const SDL_Color& color )
    {
        setColor( color.r, color.g, color.b );
    }

    void GameTexture::setColor( SDL_Color& color )
    {
        setColor( color.r, color.g, color.b );
    }

    void GameTexture::setColor( unsigned char red, unsigned char green, unsigned char blue )
    {
        SDL_SetTextureColorMod( texture, red, green, blue );
    }

    void GameTexture::setBlendMode( SDL_BlendMode blending )
    {
        SDL_SetTextureBlendMode( texture, blending );
    }

    void GameTexture::setAlpha( unsigned char alpha )
    {
        SDL_SetTextureAlphaMod( texture, alpha );
    }

    void GameTexture::render( SDL_Renderer* renderer, SDL_Rect* rect, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
    {
        //Set rendering space and render to screen
        SDL_Rect render_rect = { rect->x, rect->y, width, height };

        //Set clip rendering dimensions
        if ( clip != NULL )
        {
            render_rect.w = clip->w;
            render_rect.h = clip->h;
        }

        //Render to screen
        if ( background )
        {
            SDL_SetRenderDrawColor( renderer, background_color.r, background_color.g, background_color.b, background_color.a );
            SDL_RenderFillRect( renderer, rect );
        }
        SDL_RenderCopyEx( renderer, texture, clip, &render_rect, angle, center, flip );
    }
};


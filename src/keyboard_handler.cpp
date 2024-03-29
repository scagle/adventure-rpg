#include "keyboard_handler.hpp"

#include <SDL.h>

#define PRESSED true
#define RELEASED false

namespace game
{
    KeyboardHandler::KeyboardHandler(){}

    int KeyboardHandler::getVerticalDirection()
    {
        return ( this->keys['s'] - this->keys['w'] );
    }

    int KeyboardHandler::getHorizontalDirection()
    {
        return ( this->keys['d'] - this->keys['a'] );
    }

    bool KeyboardHandler::isPressed( unsigned char key )
    {
        return this->keys[key] == PRESSED;
    }

    bool KeyboardHandler::isReleased( unsigned char key )
    {
        return this->keys[key] == RELEASED;
    }

    void KeyboardHandler::handleInput( SDL_Event *event )
    {
        if ( event->type == SDL_KEYDOWN )
        {
            switch ( event->key.keysym.sym )
            {
                case SDLK_w:
                    this->keys['w'] = PRESSED;
                    break;
                case SDLK_a:
                    this->keys['a'] = PRESSED;
                    break;
                case SDLK_s: 
                    this->keys['s'] = PRESSED;
                    break;
                case SDLK_d: 
                    this->keys['d'] = PRESSED;
                    break;
                default: 
                    break;
            }
        }
        else if ( event->type == SDL_KEYUP )
        {
            switch ( event->key.keysym.sym )
            {
                case SDLK_w:
                    this->keys['w'] = RELEASED;
                    break;
                case SDLK_a: 
                    this->keys['a'] = RELEASED;
                    break;
                case SDLK_s: 
                    this->keys['s'] = RELEASED;
                    break;
                case SDLK_d: 
                    this->keys['d'] = RELEASED;
                    break;
                default: 
                    break;
            }
        }
    }
};

#include "sdl_utils.hpp" 

#include <stdint.h>
#include <SDL.h>

namespace game
{
    namespace utils
    {
        uint32_t colorToNumber( SDL_Color color )
        {
            return ( (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b) );
        }
    };
};

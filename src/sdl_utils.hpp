#pragma once

// Forward Declarations
class SDL_Color;

#include <stdint.h>

namespace game
{
    namespace utils
    {
        uint32_t colorToNumber(SDL_Color color);
    };
};

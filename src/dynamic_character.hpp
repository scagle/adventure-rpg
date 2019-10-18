#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "solid.hpp" 
#include "character.hpp" 

namespace game
{
    class DynamicCharacter : public Character
    {
        float actual_x; 
        float actual_y;
        float velocity_x;
        float velocity_y;
    };
};

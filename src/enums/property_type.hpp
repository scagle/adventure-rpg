#pragma once

namespace game
{
    enum class PropertyType
    {
        STACKABLE, // Dont pop off container stack when called, just push new one with priority
        NO_PROMPT, // Dont show the prompt dialog above character's head 
    };
};


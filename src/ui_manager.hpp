#pragma once
#include "menu_handler.hpp"
#include "dialog_handler.hpp"
#include "travel_handler.hpp"

namespace game
{
    class UIManager
    {
        static MenuHandler menu_handler;
        static DialogHandler dialog_handler;
        static TravelHandler travel_handler;


    };
};

#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "globals.hpp"
#include "option.hpp"

namespace game
{
    class Menu
    {
        private:
        std::string title = "";
        std::vector< Option > options;
        SDL_Color bg = MENU_BACKGROUND_COLOR;
        unsigned int current_option = 0;

        public:
        Menu();
        Menu(std::string);
        Menu(std::string, std::vector< Option > options);
        void up();
        void down();
        Option getOption();
        std::vector< Option >* getOptions();
    };
}

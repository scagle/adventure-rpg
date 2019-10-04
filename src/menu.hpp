#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "globals.hpp"
#include "option.hpp"

namespace game
{
        //TODO: Make pushDialog/pushMenu push copy of dialog/menu so that more than one of them can appear.
        //      Also see if you can make the Font_Textures static, so that they don't have to be created
        //      everytime a new dialog/menu is created
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
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        void up();
        void down();
        Option* getOption();
        std::vector< Option >* getOptions();
    };
};

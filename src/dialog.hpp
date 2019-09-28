#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "enums/direction.hpp"

namespace game
{
        //TODO: Make pushDialog/pushMenu push copy of dialog/menu so that more than one of them can appear.
        //      Also see if you can make the Font_Textures static, so that they don't have to be created
        //      everytime a new dialog/menu is created
    class Dialog
    {
        public:
        struct Choice
        {
            std::string text;
            std::string action;
        };

        private:
        std::vector< std::string > pages;
        std::vector< Choice > choices;
        unsigned int page_index = 0;
        unsigned int choice_index = 0;
        SDL_Rect box;

        public:
        Dialog() { }
        Dialog(std::vector< std::string > p, std::vector< Choice > c) : pages(p), choices(c) { }

        void setAnchor(int, int);

        virtual void render( SDL_Renderer *renderer );
        virtual void update();

        Dialog::Choice* getChoice() { return &(this->choices[choice_index]); };
        void left() { if (choice_index > 0) choice_index--; };
        void right() { if (choice_index < choices.size()) choice_index++; };
    };
};

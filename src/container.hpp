#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "text_box.hpp"
#include "button_box.hpp"

namespace game
{
    enum ContainerFormat
    {
        MENU,
        DIALOG,
        TRAVEL,
    };

    class Container
    {
        private:
        ContainerFormat format;
        std::string title = "";
        SDL_Rect box;
        std::vector< TextBox > text_boxes;
        std::vector< ButtonBox > button_boxes;
        float divider_ratio = 0.5;               // where to split the '|' or '-'. IE: [  text  | buttons ] = 0.5

        public:
        Container() { }
        virtual ~Container() { }
        virtual ContainerFormat getFormat() { return this->format; }

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    
    };
};

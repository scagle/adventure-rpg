#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "text_box.hpp"
#include "button_box.hpp"
#include "enums/direction.hpp"

namespace game
{
    //enum ContainerFormat
    //{
    //    MENU,
    //    DIALOG,
    //    TRAVEL,
    //};

    enum class ContainerOrientation
    {
        VERTICAL,
        HORIZONTAL,
    };

    class Container
    {
        protected:
        //ContainerFormat format;
        std::string title = "";
        SDL_Rect box;
        // TODO: Potentially optimize these if I'm creating a bunch of containers
        std::vector< TextBox > text_boxes;
        std::vector< ButtonBox > button_boxes;
        SDL_Color background; 
        SDL_Color foreground;

        int text_index = 0;              // Current index of text_boxes (at last index the buttons will show up)
        int selected_index = 0;          // Current index of selected button
        float divider_ratio = 0.8; // where to put vertical / horizontal split. IE: [  text  | buttons ] = 0.5 (50%)
        ContainerOrientation orientation = ContainerOrientation::VERTICAL;       

        public:
        Container();
        Container(std::vector< TextBox >, std::vector< ButtonBox >);
        Container(std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerOrientation orientation);
        virtual ~Container() { }
        //virtual ContainerFormat getFormat() { return this->format; }

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        void moveCursor(Direction dir);
        std::string select();
    
    };
};

#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "text_box.hpp"
#include "button_box.hpp"
#include "enums/direction.hpp"
#include "enums/container_enums.hpp"

namespace game
{
    //enum ContainerFormat
    //{
    //    MENU,
    //    DIALOG,
    //    TRAVEL,
    //};

    class Container
    {
        protected:
        //ContainerFormat format;
        std::string title = "";
        SDL_Rect box;
        // TODO: Potentially optimize these if I'm creating a bunch of containers
        std::vector< TextBox > text_boxes;
        std::vector< ButtonBox > button_boxes;
        int text_index = 0;              // Current index of text_boxes (at last index the buttons will show up)
        int selected_index = 0;          // Current index of selected button
        float divider_ratio = 0.8; // where to put vertical / horizontal split. IE: [  text  | buttons ] = 0.5 (50%)
        ContainerType type = ContainerType::FLOATING;
        std::string id; 
        ContainerOrientation orientation = ContainerOrientation::VERTICAL;       
        SDL_Color background; 
        SDL_Color foreground;

        public:
        Container();
        Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs);
        Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerType type );
        Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerType type, std::string id );
        Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerType type, int emit_x, int emit_y);

        virtual ~Container() { }
        //virtual ContainerFormat getFormat() { return this->format; }

        virtual void initializeBox(int emit_x, int emit_y);
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        virtual bool hasTextBoxes() { return (text_boxes.size() > 0); }
        virtual bool hasButtonBoxes() { return (button_boxes.size() > 0); }
        virtual bool isTotallyEmpty() { return (text_boxes.size() == 0 && button_boxes.size() == 0); }  
        virtual std::string getID() { return id; }
        virtual void setEmittedPosition(int emit_x, int emit_y);
        void moveCursor(Direction dir);
        std::string select();
    
    };
};

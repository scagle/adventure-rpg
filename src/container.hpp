#pragma once

// Forward Declarations
namespace game
{
    class Character;
    enum class Direction;
};

#include "text_box.hpp"
#include "button_box.hpp"
#include "datatypes/properties.hpp"

#include "enums/direction.hpp"
#include "enums/container_orientation.hpp"
#include "enums/container_type.hpp"

#include <SDL.h>
#include <string>
#include <vector>

namespace game
{
    class Container
    {
        protected:
            std::string title = "";
            SDL_Rect box;

            // TODO: Potentially optimize these if I'm creating a bunch of containers
            std::vector< TextBox > text_boxes;
            std::vector< ButtonBox > button_boxes;
            ContainerType type = ContainerType::FLOATING;
            std::string id; 
            Properties properties;
            SDL_Color background; 
            SDL_Color foreground;
            Character* character = nullptr;
            bool show_prompt = false;   // boolean to control whether container must be prompted first (IE: npc dialogs )
            int text_index = 0;         // Current index of text_boxes (at last index the buttons will show up)
            int selected_index = 0;     // Current index of selected button

            // Constants until I need a way to change them
            float divider_ratio = 0.8;  // where to put vertical / horizontal split. IE: [  text  | buttons ] = 0.5 (50%)
            int buffer = 2;       // buffer of pixels around edges
            ContainerOrientation orientation = ContainerOrientation::VERTICAL;       

        public:
            Container();
            Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, 
                    Properties properties);
            Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerType type, 
                    Properties properties );
            Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerType type, std::string id, 
                    Properties properties );
            Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerType type, int emit_x, int emit_y, 
                    Properties properties);

            virtual ~Container() { }
            //virtual ContainerFormat getFormat() { return this->format; }

            virtual void initializeBox(int emit_x, int emit_y);

            virtual bool hasTextBoxes() { return (text_boxes.size() > 0); }
            virtual bool hasButtonBoxes() { return (button_boxes.size() > 0); }
            virtual bool isTotallyEmpty() { return (text_boxes.size() == 0 && button_boxes.size() == 0); }  

            virtual std::string getID() { return id; }
            virtual Properties* getProperties() { return &( properties ); }
            virtual Character* getCharacter() { return character; }
            virtual std::string getSelectedAction() { return button_boxes[selected_index].getAction(); }
            virtual Properties* getSelectedProperties() { return button_boxes[selected_index].getProperties(); }

            virtual void setEmittedPosition(int emit_x, int emit_y);
            virtual void setCharacter(Character* character) { this->character = character; }
            virtual void moveCursor(Direction dir);
            virtual std::string select();

            virtual void render( SDL_Renderer *renderer );
            virtual void update();
            void renderPrompt( SDL_Renderer *renderer );
            void renderMenu( SDL_Renderer *renderer );
            void renderTextWithButtons( SDL_Renderer *renderer );
            void renderText( SDL_Renderer *renderer );
    
    };
};

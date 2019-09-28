#include <SDL.h>
#include <iostream>
#include <set>
#include <stdio.h>
#include "menu_handler.hpp"
#include "menu.hpp"
#include "globals.hpp"
#include "option.hpp"
#include "dialog.hpp"

namespace game
{
    // Static Declarations
    std::unordered_map< std::string, Container > MenuHandler::containers;       // < container_id , container >
    std::unordered_map< std::string, SDL_Texture > MenuHandler::text_textures;  // < container_id , texture   >
    std::stack< Container* > MenuHandler::container_stack;
    std::vector< SDL_Texture > MenuHandler::text_textures;

    MenuHandler::MenuHandler()
    {
        this->containers = {};
        this->container_stack = {};
    }

    bool MenuHandler::initContainers()
    {
        /*! TODO: Could be made more efficient by passing by reference instead of value
         *  \todo Could be made more efficient by passing by reference instead of value
         */
        this-> = 
        { 
            { 
                "main" ,            // id
                Container(          // Container
                    "Main Menu", 
                    { 
                        Button( "Save", "save", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load", "load", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ),
                        Button( "Exit", "",     WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                    } 
                ) 
            },
            { 
                "save" ,            // id
                Container(          // Container
                    "Save Page", 
                    { 
                        Button( "Save 1", "save1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 2", "save2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 3", "save3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 4", "save4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 5", "save5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 6", "save6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 7", "save7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 8", "save8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Save 9", "save9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                    } 
                ) 
            }, 
            { 
                "load" ,            // id
                Container(          // Container
                    "Load Page", 
                    { 
                        Button( "Load 1", "load1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 2", "load2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 3", "load3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 4", "load4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 5", "load5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 6", "load6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 7", "load7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 8", "load8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Button( "Load 9", "load9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                    } 
                ) 
            }, 
            { 
                "warning" ,         // id
                Container(          // Container
                    "Warning", 
                    { 
                        Button( "warning!!!", "main", WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ),
                    } 
                ) 
            },
        };

        return true;
    }

    bool MenuHandler::initTextTextures()
    {
        SDL_Renderer *renderer = GameData::getActiveRenderer();
        for ( auto& container_mapping : containers )
        {
            for ( auto& textbox_mapping : container_mapping.second() )
            {
                SDL_Surface *text_surface = TTF_RenderText_Solid( font, text.c_str(), foreground );
                message = SDL_CreateTextureFromSurface( renderer, text_surface );
                SDL_FreeSurface(text_surface);
            }
        }
    }

    void MenuHandler::pushContainer(std::string next)
    {
        menu_stack.push(&menus[next]);
    }

    void MenuHandler::pushDialog(std::string next, int entity_center_x, int entity_center_y)
    {
        dialogs[next].setAnchor(entity_center_x, entity_center_y);
        dialog_stack.push(&dialogs[next]);
    }

    void MenuHandler::popContainer()
    {
        menu_stack.pop();
    }

    void MenuHandler::popDialog()
    {
        dialog_stack.pop();
    }

    void MenuHandler::moveContainer(Direction dir)
    {
        if (dir == Direction::UP)
            this->menu_stack.top()->up();
        else if (dir == Direction::DOWN)
            this->menu_stack.top()->down();
        else
            printf("Invalid Direction! game::MenuHandler::moveContainer()\n");
    }

    void MenuHandler::moveDialog(Direction dir)
    {
        if (dir == Direction::LEFT)
            this->dialog_stack.top()->left();
        else if (dir == Direction::RIGHT)
            this->dialog_stack.top()->right();
        else
            printf("Invalid Direction! game::MenuHandler::moveDialog()\n");
    }

    void MenuHandler::selectContainer()
    {
        Option *selected_option = this->menu_stack.top()->getOption();
        std::string text = selected_option->getText();
        std::string next = selected_option->getNext();
        if (next != "")
        {
            menu_stack.push(&menus[next]);
        }

        printf("Pressed: '%s' which calls '%s'\n", text.c_str(), next.c_str());
    }

    void MenuHandler::selectDialog()
    {
        Dialog::Choice *choice = this->dialog_stack.top()->getChoice();
        std::string text = choice->text;
        std::string action = choice->action;
    }

    Container* MenuHandler::getContainer()
    {
        if (menu_stack.size() == 0)
            std::cout << "*** Warning: No menus on stack! (ui/menu_handler.cpp -> getMenu())";

        return this->menu_stack.top();
    }

    Dialog* MenuHandler::getDialog()
    {
        if (dialog_stack.size() == 0)
            std::cout << "*** Warning: No dialogs on stack! (ui/menu_handler.cpp -> getDialog())";

        return this->dialog_stack.top();
    }

    bool MenuHandler::inContainer()
    {
        return (menu_stack.size() > 0);
    }

    bool MenuHandler::inDialog()
    {
        return (dialog_stack.size() > 0);
    }

    void MenuHandler::render( SDL_Renderer *renderer )
    {
        if ( inMenu() )
            getMenu()->render( renderer );
        else if ( inDialog() )
        {
            getDialog()->render( renderer );
        }
    }

    void MenuHandler::update()
    {

    }


    void MenuHandler::save()
    {

    }

    void MenuHandler::load()
    {

    }

    void MenuHandler::quit()
    {

    }
}

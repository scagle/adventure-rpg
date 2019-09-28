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
    std::unordered_map< std::string, Menu > MenuHandler::menus;
    std::unordered_map< std::string, Dialog > MenuHandler::dialogs;
    std::stack< Menu* > MenuHandler::menu_stack;
    std::stack< Dialog* > MenuHandler::dialog_stack;
    std::set< std::string > MenuHandler::dialog_set;

    MenuHandler::MenuHandler()
    {
        this->menus = {};
        this->dialogs = {};
    }

    bool MenuHandler::loadMenus()
    {
        /*! TODO: Could be made more efficient by passing by reference instead of value
         *  \todo Could be made more efficient by passing by reference instead of value
         */
/////// MENU /////////////////////////////////////////////////////////////////////////////////////////////////////
        this->menus = 
        { 
            { 
                "main" , 
                Menu( 
                    "Main Menu", 
                    { 
                        Option( "Save", "save", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load", "load", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ),
                        Option( "Exit", "",     WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                    } 
                ) 
            },
            { 
                "save" , 
                Menu( 
                    "Save Page", 
                    { 
                        Option( "Save 1", "save1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 2", "save2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 3", "save3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 4", "save4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 5", "save5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 6", "save6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 7", "save7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 8", "save8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 9", "save9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                    } 
                ) 
            }, 
            { 
                "load" , 
                Menu( 
                    "Load Page", 
                    { 
                        Option( "Load 1", "load1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 2", "load2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 3", "load3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 4", "load4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 5", "load5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 6", "load6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 7", "load7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 8", "load8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 9", "load9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                    } 
                ) 
            }, 
            { 
                "warning" , 
                Menu( 
                    "Warning", 
                    { 
                        Option( "warning!!!", "main", WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ),
                    } 
                ) 
            },
        };

/////// DIALOGS /////////////////////////////////////////////////////////////////////////////////////////////////
//        this->dialogs = { {"test", Dialog()} }; 

        this->dialogs = 
        { 
            { 
                "portal_to_forest" , 
                Dialog( 
                    { 
                        "Travel to Forest?", 
                    }, 
                    { 
                        Dialog::Choice{"Yes", "travel_forest"}, 
                        Dialog::Choice{"No", "leave"}, 
                    }
                )
            },
            { 
                "home_merchant" , 
                Dialog( 
                    { 
                        "Hello there adventurer! Would you like to browse my wares?",
                    }, 
                    { 
                        Dialog::Choice{"Buy", "shop0_buy"}, 
                        Dialog::Choice{"Sell", "shop0_sell"}, 
                        Dialog::Choice{"BEGONE!", "leave"},
                    }
                )
                
            }
        };

        return true;
    }

    void MenuHandler::pushMenu(std::string next)
    {
        menu_stack.push(&menus[next]);
    }

    void MenuHandler::pushDialog(std::string next, int entity_center_x, int entity_center_y)
    {
        dialogs[next].setAnchor(entity_center_x, entity_center_y);
        dialog_stack.push(&dialogs[next]);
    }

    void MenuHandler::popMenu()
    {
        menu_stack.pop();
    }

    void MenuHandler::popDialog()
    {
        dialog_stack.pop();
    }

    void MenuHandler::moveMenu(Direction dir)
    {
        if (dir == Direction::UP)
            this->menu_stack.top()->up();
        else if (dir == Direction::DOWN)
            this->menu_stack.top()->down();
        else
            printf("Invalid Direction! game::MenuHandler::moveMenu()\n");
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

    void MenuHandler::selectMenu()
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

    Menu* MenuHandler::getMenu()
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

    bool MenuHandler::inMenu()
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

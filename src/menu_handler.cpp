#include <SDL.h>
#include <iostream>
#include "menu_handler.hpp"
#include "menu.hpp"
#include "globals.hpp"

namespace game
{
    MenuHandler::MenuHandler()
    {
        this->menus = {};
    }

    bool MenuHandler::loadMenus()
    {
        this->menus = { 
            {"main" , Menu( "Main Menu", { 
                        Option( "Save", "save", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT  ), //TODO Pass function pointer to appropriate methods
                        Option( "Load", "load", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT  ),
                        Option( "Exit", "",     WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ) 
                    } ) },
            {"save" , Menu( "Save Page", { 
                        Option( "Save 1", "save1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 2", "save2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 3", "save3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 4", "save4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 5", "save5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 6", "save6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 7", "save7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 8", "save8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Save 9", "save9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ) 
                    } ) }, 
            {"load" , Menu( "Load Page", { 
                        Option( "Load 1", "load1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 2", "load2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 3", "load3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 4", "load4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 5", "load5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 6", "load6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 7", "load7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 8", "load8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ), 
                        Option( "Load 9", "load9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ) 
                    } ) }, 
            {"warning" , Menu( "Warning", { 
                        Option( "warning!!!", "main", WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR, DEFAULT_FONT ) 
                    } ) } 
        };
        return true;
    }

    void MenuHandler::pushMenu(std::string key)
    {
        menu_stack.push(menus[key]);
    }

    void MenuHandler::popMenu()
    {
        menu_stack.pop();
    }

    void MenuHandler::moveMenu(Direction dir)
    {
        if (dir == UP)
            this->menu_stack.top().up();
        else
            this->menu_stack.top().down();
    }

    void MenuHandler::selectMenu()
    {
        this->menu_stack.top().getOption();
    }

    Menu& MenuHandler::getMenu()
    {
        if (menu_stack.size() == 0)
            std::cout << "*** Warning: No menu's on stack! (ui/menu_handler.cpp -> getMenu())";

        return this->menu_stack.top();
    }

    bool MenuHandler::inMenu()
    {
        return (this->menu_stack.size());
    }

    void MenuHandler::render( SDL_Renderer *renderer )
    {
        if ( !inMenu() )
            return;

        // Draw Transparent Overlay
        SDL_Rect menu_box = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 }; 
        SDL_SetRenderDrawColor( renderer, 
                                MENU_BACKGROUND_COLOR.r,
                                MENU_BACKGROUND_COLOR.g,
                                MENU_BACKGROUND_COLOR.b,
                                MENU_BACKGROUND_COLOR.a
        );
        SDL_RenderFillRect( renderer, &menu_box );
        // Get Options
        Menu menu = getMenu();
        std::vector< Option > *options = menu.getOptions();
        for ( Option option : (*options) )
        {
            int option_height = (menu_box.h - 60) / options->size();
            for (int i = 0; i < (int)options->size(); i++)
            {
                option.render( renderer, &menu_box, option_height, i );
            }
        }
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

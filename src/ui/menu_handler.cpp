#include <SDL.h>
#include <iostream>
#include "menu_handler.hpp"
#include "menu.hpp"
#include "../globals.hpp"

MenuHandler::MenuHandler()
{
    this->menus = {};
}

void MenuHandler::loadMenus()
{
    this->menus = { 
        {"main" , Menu( "Main Menu", { 
                    { "Save", "save", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, //TODO Pass function pointer to appropriate methods
                    { "Load", "load", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR },
                    { "Exit", "",     OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR } 
                } ) },
        {"save" , Menu( "Save Page", { 
                    { "Save 1", "save1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 2", "save2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 3", "save3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 4", "save4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 5", "save5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 6", "save6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 7", "save7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 8", "save8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Save 9", "save9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR } 
                } ) }, 
        {"load" , Menu( "Load Page", { 
                    { "Load 1", "load1", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 2", "load2", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 3", "load3", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 4", "load4", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 5", "load5", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 6", "load6", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 7", "load7", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 8", "load8", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR }, 
                    { "Load 9", "load9", OPTION_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR } 
                } ) }, 
        {"warning" , Menu( "Warning", { 
                    { "warning!!!", "main", WARNING_BACKGROUND_COLOR, OPTION_FOREGROUND_COLOR } 
                } ) } 
    };
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

void MenuHandler::save()
{

}

void MenuHandler::load()
{

}

void MenuHandler::quit()
{

}

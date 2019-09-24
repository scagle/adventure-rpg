#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "globals.hpp"

struct Option
{
    std::string text;
    std::string next;
    SDL_Color bg;
    SDL_Color fg;
    void (*call_function)();
};

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
    void up();
    void down();
    Option getOption();
    std::vector< Option >* getAllOptions();
};

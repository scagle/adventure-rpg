#include <SDL.h>
#include <string>
#include <vector>
#include "menu.hpp"

namespace game
{
    Menu::Menu()
    {
        this->title = "";
        this->options = std::vector< Option >();
    }

    Menu::Menu(std::string title)
    {
        this->title = title;
        this->options = std::vector< Option >();
    }

    Menu::Menu(std::string title, std::vector< Option > options)
    {
        this->title = title;
        this->options = options;
    }

    void Menu::render( SDL_Renderer *renderer )
    {
        // Draw Transparent Overlay
        SDL_Rect screen_box = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; 
        SDL_SetRenderDrawColor( renderer, 
                                BLUR_BACKGROUND_COLOR.r,
                                BLUR_BACKGROUND_COLOR.g,
                                BLUR_BACKGROUND_COLOR.b,
                                BLUR_BACKGROUND_COLOR.a
        );
        SDL_RenderFillRect( renderer, &screen_box );
        // Draw Menu Background
        SDL_Rect menu_box = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 }; 
        SDL_SetRenderDrawColor( renderer, 
                                MENU_BACKGROUND_COLOR.r,
                                MENU_BACKGROUND_COLOR.g,
                                MENU_BACKGROUND_COLOR.b,
                                MENU_BACKGROUND_COLOR.a
        );
        SDL_RenderFillRect( renderer, &menu_box );

        // Render Options
        for (unsigned int i = 0; i < options.size(); i++)
        {
            int option_height = (menu_box.h - 60) / options.size();
            bool selected = (current_option == i);
            options[i].render( renderer, &menu_box, option_height, i, selected);
        }
    }

    void Menu::update()
    {

    }

    void Menu::up() 
    { 
        if (this->current_option > 0)
            this->current_option--; 
    }
    void Menu::down() 
    { 
        if (this->current_option < this->options.size() - 1)
            this->current_option++;
    }

    Option* Menu::getOption() 
    {
        return &(options[current_option]);
    }

    std::vector< Option >* Menu::getOptions()
    {
        return &(this->options);
    }
}

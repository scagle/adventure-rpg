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

    Option Menu::getOption() 
    {
        return (this->options[current_option]);
    }

    std::vector< Option >* Menu::getAllOptions()
    {
        return &(this->options);
    }
}

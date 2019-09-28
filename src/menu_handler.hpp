#pragma once
#include <unordered_map>
#include <set>
#include <stack>
#include <vector>
#include "menu.hpp"
#include "dialog.hpp"
#include "enums/direction.hpp"

namespace game
{
    class MenuHandler : public InterfaceHandler
    {
        private:
        static std::unordered_map< std::string, Menu > menus;
        static std::stack< Menu* > menu_stack;

        public:
        MenuHandler();

        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        void save();
        void load();
        void quit();
    };
}

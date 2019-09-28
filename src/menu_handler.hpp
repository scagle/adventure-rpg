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
    class MenuHandler
    {
        private:
        static std::unordered_map< std::string, Menu > menus;
        static std::unordered_map< std::string, Dialog > dialogs;
        static std::stack< Menu* > menu_stack;
        static std::stack< Dialog* > dialog_stack;
        static std::set< std::string > dialog_set;


        public:
        MenuHandler();

        bool loadMenus();
        static void pushMenu(std::string);
        static void pushDialog(std::string, int, int);
        void popMenu();
        void popDialog();
        void moveMenu(Direction);
        void moveDialog(Direction);
        void selectMenu();
        void selectDialog();
        Menu* getMenu();
        Dialog* getDialog();
        static bool inMenu();
        static bool inDialog();
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        void save();
        void load();
        void quit();
    };
}

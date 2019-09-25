#pragma once
#include <unordered_map>
#include <stack>
#include <vector>
#include "menu.hpp"

namespace game
{
    class MenuHandler
    {
        private:
        std::unordered_map<std::string, Menu > menus;
        std::stack< Menu > menu_stack;
        /*! TODO: - Create basic main_menu with some options that call other menus with options
         *          - Test options
         *        - Update rendering
         *          - Use actual renderer
         *          - Implement Alpha Channels
         *          - Get text rendering
         *        - Have KeyboardHandler give navigation capabilities to menu
         *        - Verify that alpha is either 0=invis, 255=vis or vice versa
         *        - Figure out how to input text for names / output text to display ( is library required or what? )
         *        - Create Friendly NPCs
         *          - Figure out how to speak to them (respecting a specific individual in crowded area, and not being random)
         *        - Brainstorm Fights / S scenes
         *          - Brainstorm how/where fights should begin
         *          - Create Non-Friendly NPCs
         *        - Evaluate whether Tensorflow is feasible for ANYTHING
         *        - Brainstorm Inventory
         *        - Brainstorm Equipments
         *        - Implement Currency
         *          - Trading / Shops
         *        - Implement Saving / Loading
         *        - Write story
         *          - Create more maps
         *          - Win / Loss conditions
         */

        public:
        MenuHandler();
        enum Direction{UP, DOWN};

        void loadMenus();
        void pushMenu(std::string);
        void popMenu();
        void moveMenu(Direction);
        void selectMenu();
        Menu& getMenu();
        bool inMenu();
        virtual void render( SDL_Renderer *renderer );
        void save();
        void load();
        void quit();
    };
}

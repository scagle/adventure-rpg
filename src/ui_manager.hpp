#pragma once
#include "menu_handler.hpp"
#include "dialog_handler.hpp"
//#include "travel_handler.hpp"
#include "event.hpp"
#include "enums/ui.hpp"

namespace game
{
    class UIManager
    {
        private:
        static MenuHandler menu_handler;
        static DialogHandler dialog_handler;
//        static TravelHandler travel_handler;

        public:
        UIManager() { }
        virtual ~UIManager() { }

        static void handleEvent(Event event);
        static bool inUI(UI);
        void handleInput(SDL_Event *event);
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

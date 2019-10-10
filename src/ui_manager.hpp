#pragma once
#include <string> 
#include "menu_handler.hpp"
#include "dialog_handler.hpp"
#include "travel_handler.hpp"
#include "event.hpp"
#include "enums/ui.hpp"

namespace game
{
    class UIManager
    {
        private:
        static MenuHandler menu_handler;
        static DialogHandler dialog_handler;
        static TravelHandler travel_handler;

        public:
        UIManager() { }
        virtual ~UIManager() { }

        static bool handleEvent(Event* event);
        static void handleInput(SDL_Event*);
        static bool inUI(UI);
        static bool inUI(UI, std::string);
        static std::string getID(UI);
        bool initializeUIHandlers();
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

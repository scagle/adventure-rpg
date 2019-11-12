#pragma once

// Forward Declarations
namespace game
{
    class Event;
    enum class UI;
};
class SDL_Renderer;
union SDL_Event;

#include "menu_handler.hpp"
#include "dialog_handler.hpp"
#include "travel_handler.hpp"

#include <string> 

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

            static bool handleEvent( Event* event );
            static void handleInput( SDL_Event* );
            bool initializeUIHandlers();

            static bool inUI( UI );
            static bool inUI( UI, std::string );
            static std::string getID( UI );

            virtual void render( SDL_Renderer *renderer );
            virtual void update();
    };
};

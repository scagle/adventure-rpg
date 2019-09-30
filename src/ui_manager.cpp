#include "ui_manager.hpp"
#include "menu_handler.hpp"
#include "dialog_handler.hpp"
//#include "travel_handler.hpp"
#include "event.hpp"

namespace game
{
    MenuHandler UIManager::menu_handler;
    DialogHandler UIManager::dialog_handler;
//    TravelHandler UIManager::travel_handler;

    void UIManager::handleEvent( Event event )
    {
        // TODO: 
    }

    bool UIManager::inUI(UI ui)
    {
        switch (ui)
        {
            case MENU:
                return menu_handler.inContainer();
            case DIALOG:
                return dialog_handler.inContainer();
            case TRAVEL:
                printf("Unimplemented!");
                return false;
                //return travel_handler.inContainer();
    }
    void UIManager::handleInput( SDL_Event *event )
    {
        // TODO: 
    }

    void UIManager::render( SDL_Renderer *renderer )
    {

    }

    void UIManager::update()
    {
        
    }
};

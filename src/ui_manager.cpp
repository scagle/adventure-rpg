#include "ui_manager.hpp"
#include "menu_handler.hpp"
#include "dialog_handler.hpp"
#include "travel_handler.hpp"
#include "event.hpp"

namespace game
{
    MenuHandler UIManager::menu_handler;
    DialogHandler UIManager::dialog_handler;
    TravelHandler UIManager::travel_handler;

    bool UIManager::handleEvent( UI target, Event* event )
    {
        switch (target)
        {
            case UI::MENU:
                return menu_handler.handleEvent(event);
            case UI::DIALOG:
                return dialog_handler.handleEvent(event);
            case UI::TRAVEL:
                return travel_handler.handleEvent(event);
            default:
                printf("Unknown Event Type (ui_manager.cpp -> handleEvent())");
                return false;
        }
    }

    void UIManager::handleInput( SDL_Event *event )
    {
        const uint8_t *key_states = SDL_GetKeyboardState(NULL);
        switch ( event->key.keysym.sym )
        {
            case SDLK_ESCAPE:
                if ( key_states[SDL_SCANCODE_ESCAPE] ) 
                {
                    if ( menu_handler.inContainer() )
                        menu_handler.popContainer();
                    else if ( dialog_handler.inContainer() )
                        dialog_handler.popContainer();
                    else if ( travel_handler.inContainer() )
                        travel_handler.popContainer();
                    else
                        menu_handler.pushContainer("main");
                }
                break;

            case SDLK_j:
                if ( key_states[SDL_SCANCODE_J] ) 
                {
                    if ( menu_handler.inContainer() )
                        menu_handler.moveContainer(Direction::DOWN);
                    else if ( dialog_handler.inContainer() )
                        dialog_handler.moveContainer(Direction::DOWN);
                    else if ( travel_handler.inContainer() )
                        travel_handler.moveContainer(Direction::DOWN);
                }
                break;

            case SDLK_k:
                if ( key_states[SDL_SCANCODE_K] ) 
                {
                    if ( menu_handler.inContainer() )
                        menu_handler.moveContainer(Direction::UP);
                    else if ( dialog_handler.inContainer() )
                        dialog_handler.moveContainer(Direction::UP);
                    else if ( travel_handler.inContainer() )
                        travel_handler.moveContainer(Direction::UP);
                }
                break;

            case SDLK_RETURN:
                if ( key_states[SDL_SCANCODE_RETURN] ) 
                {
                    if ( menu_handler.inContainer() )
                        menu_handler.selectContainer();
                    else if ( dialog_handler.inContainer() )
                        dialog_handler.selectContainer();
                }
                break;
        }
    }

    bool UIManager::inUI( UI ui )
    {
        switch (ui)
        {
            case UI::MENU:
                return menu_handler.inContainer();
            case UI::DIALOG:
                return dialog_handler.inContainer();
            case UI::TRAVEL:
                return travel_handler.inContainer();
            default:
                printf("Invalid UI (ui_manager.cpp -> inUI(UI))\n");
                break;
        }
        return false;
    }

    bool UIManager::inUI( UI ui, std::string id )
    {
        switch (ui)
        {
            case UI::MENU:
                return menu_handler.checkActiveContainer();
            case UI::DIALOG:
                return dialog_handler.checkActiveContainer();
            case UI::TRAVEL:
                return travel_handler.checkActiveContainer();
            default:
                printf("Invalid UI (ui_manager.cpp -> inUI(UI, std::string))\n");
                break;
        }
        return false;
    }


    std::string UIManager::getID( UI ui )
    {
        switch (ui)
        {
            case UI::MENU:
                return menu_handler.getContainerID();
            case UI::DIALOG:
                return dialog_handler.getContainerID();
            case UI::TRAVEL:
                return travel_handler.getContainerID();
            default:
                printf("Invalid UI (ui_manager.cpp -> getUI())\n");
                break;
        }
        return "";
    }

    bool UIManager::initializeUIHandlers()
    {
        if ( !menu_handler.loadContainers() )
        {
            printf("ui_manager.cpp : MenuHandler could not be initialized!\n");
            return false;
        }

        if ( !dialog_handler.loadContainers() )
        {

            printf("ui_manager.cpp : DialogHandler could not be initialized!\n");
            return false;
        }

        if ( !travel_handler.loadContainers() )
        {
            printf("ui_manager.cpp : TravelHandler could not be initialized!\n");
            return false;
        }
        return true;
    }

    void UIManager::render( SDL_Renderer *renderer )
    {
        menu_handler.render( renderer );
        dialog_handler.render( renderer );
        travel_handler.render( renderer );
    }

    void UIManager::update()
    {
        
    }
};

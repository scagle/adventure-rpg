#include <SDL.h>
#include <iostream>
#include <vector>
#include <set>
#include <stdio.h>
#include "menu_handler.hpp"
#include "menu.hpp"
#include "globals.hpp"
#include "option.hpp"
#include "container.hpp"
#include "text_box.hpp"
#include "button_box.hpp"

namespace game
{

    bool MenuHandler::loadContainers()
    {
        /*! TODO: Could be made more efficient by passing by reference instead of value
         *  \todo Could be made more efficient by passing by reference instead of value
         */
        this->containers = 
        { 
            { 
                "main" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Save", DEFAULT_FONT, "save" ), 
                        ButtonBox( "Load", DEFAULT_FONT, "load" ),
                        ButtonBox( "Exit", DEFAULT_FONT, ""     ),
                    },
                    ContainerType::SCREEN
                ) 
            },
            { 
                "save" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Save 1", DEFAULT_FONT, "save1" ), 
                        ButtonBox( "Save 2", DEFAULT_FONT, "save2" ), 
                        ButtonBox( "Save 3", DEFAULT_FONT, "save3" ), 
                        ButtonBox( "Save 4", DEFAULT_FONT, "save4" ), 
                        ButtonBox( "Save 5", DEFAULT_FONT, "save5" ), 
                        ButtonBox( "Save 6", DEFAULT_FONT, "save6" ), 
                        ButtonBox( "Save 7", DEFAULT_FONT, "save7" ), 
                        ButtonBox( "Save 8", DEFAULT_FONT, "save8" ), 
                        ButtonBox( "Save 9", DEFAULT_FONT, "save9" ), 
                    },
                    ContainerType::SCREEN
                ) 
            }, 
            { 
                "load" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Load 1", DEFAULT_FONT, "load1" ), 
                        ButtonBox( "Load 2", DEFAULT_FONT, "load2" ), 
                        ButtonBox( "Load 3", DEFAULT_FONT, "load3" ), 
                        ButtonBox( "Load 4", DEFAULT_FONT, "load4" ), 
                        ButtonBox( "Load 5", DEFAULT_FONT, "load5" ), 
                        ButtonBox( "Load 6", DEFAULT_FONT, "load6" ), 
                        ButtonBox( "Load 7", DEFAULT_FONT, "load7" ), 
                        ButtonBox( "Load 8", DEFAULT_FONT, "load8" ), 
                        ButtonBox( "Load 9", DEFAULT_FONT, "load9" ), 
                    },
                    ContainerType::SCREEN
                ) 
            }, 
            { 
                "warning" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "warning!!!", DEFAULT_FONT, "main" ),
                    },
                    ContainerType::SCREEN
                ) 
            },
        };
        return true;
    }

    bool MenuHandler::handleEvent( Event *event )
    {
        printf("menu_handler recieved: %s", event->getID().c_str());
        return true;
    }

    void MenuHandler::render( SDL_Renderer *renderer )
    {
        if ( inContainer() )
            getContainer()->render( renderer );
    }

    void MenuHandler::update()
    {

    }

    void MenuHandler::save()
    {

    }

    void MenuHandler::load()
    {

    }

    void MenuHandler::quit()
    {

    }
};

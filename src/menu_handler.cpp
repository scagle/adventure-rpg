#include <SDL.h>
#include <iostream>
#include <vector>
#include <set>
#include <stdio.h>
#include "menu_handler.hpp"
#include "menu.hpp"
#include "globals.hpp"
#include "option.hpp"
#include "world.hpp"
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
                        ButtonBox( "Return", DEFAULT_FONT, "leave" ),
                        ButtonBox( "Save", DEFAULT_FONT, "save" ), 
                        ButtonBox( "Load", DEFAULT_FONT, "load" ),
                        ButtonBox( "Exit", DEFAULT_FONT, "quit" ),
                    },
                    ContainerType::SCREEN,
                    "main"
                ) 
            },
            { 
                "save" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Return", DEFAULT_FONT, "leave" ),
                        ButtonBox( "Save 1", DEFAULT_FONT, "save;1" ), 
                        ButtonBox( "Save 2", DEFAULT_FONT, "save;2" ), 
                        ButtonBox( "Save 3", DEFAULT_FONT, "save;3" ), 
                        ButtonBox( "Save 4", DEFAULT_FONT, "save;4" ), 
                        ButtonBox( "Save 5", DEFAULT_FONT, "save;5" ), 
                        ButtonBox( "Save 6", DEFAULT_FONT, "save;6" ), 
                        ButtonBox( "Save 7", DEFAULT_FONT, "save;7" ), 
                        ButtonBox( "Save 8", DEFAULT_FONT, "save;8" ), 
                        ButtonBox( "Save 9", DEFAULT_FONT, "save;9" ), 
                    },
                    ContainerType::SCREEN,
                    "save"
                ) 
            }, 
            { 
                "load" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Return", DEFAULT_FONT, "leave" ),
                        ButtonBox( "Load 1", DEFAULT_FONT, "load;1" ), 
                        ButtonBox( "Load 2", DEFAULT_FONT, "load;2" ), 
                        ButtonBox( "Load 3", DEFAULT_FONT, "load;3" ), 
                        ButtonBox( "Load 4", DEFAULT_FONT, "load;4" ), 
                        ButtonBox( "Load 5", DEFAULT_FONT, "load;5" ), 
                        ButtonBox( "Load 6", DEFAULT_FONT, "load;6" ), 
                        ButtonBox( "Load 7", DEFAULT_FONT, "load;7" ), 
                        ButtonBox( "Load 8", DEFAULT_FONT, "load;8" ), 
                        ButtonBox( "Load 9", DEFAULT_FONT, "load;9" ), 
                    },
                    ContainerType::SCREEN,
                    "load"
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
                    ContainerType::SCREEN,
                    "warning"
                ) 
            },
        };
        return true;
    }

    void MenuHandler::handleID( std::string id )
    {
        if ( id.find(";") != std::string::npos )
        {
            printf("'%s' contains a semicolon\n", id.c_str());
            return;
        }

        if ( id == "quit")
            quit();
        else if ( id == "leave" || id == "back" )
            popContainer();
        else
            pushPriorityContainer(id);
    }

    bool MenuHandler::handleEvent( Event *event )
    {
        printf("menu_handler recieved: %s\n", event->getID().c_str());
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
        printf("Trying to quit!\n");

    }
};

#include "menu_handler.hpp"

#include "gamedata.hpp"
#include "container.hpp"
#include "text_box.hpp"
#include "button_box.hpp"
#include "event.hpp"
#include "datatypes/properties.hpp"

#include "enums/property_type.hpp"
#include "globals.hpp"

#include <SDL.h>
#include <iostream>
#include <vector>
#include <set>
#include <stdio.h>

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
                        ButtonBox( "Return", DEFAULT_FONT, "leave", Properties() ),
                        ButtonBox( "Save", DEFAULT_FONT, "save", Properties( { { PropertyType::STACKABLE, 1 } } ) ), 
                        ButtonBox( "Load", DEFAULT_FONT, "load", Properties( { { PropertyType::STACKABLE, 1 } } ) ),
                        ButtonBox( "Exit", DEFAULT_FONT, "quit", Properties() ),
                    },
                    ContainerType::SCREEN,
                    "main",
                    {}
                ) 
            },
            { 
                "save" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Return", DEFAULT_FONT, "leave",  Properties() ),
                        ButtonBox( "Save 1", DEFAULT_FONT, "save_1", Properties() ), 
                        ButtonBox( "Save 2", DEFAULT_FONT, "save_2", Properties() ), 
                        ButtonBox( "Save 3", DEFAULT_FONT, "save_3", Properties() ), 
                        ButtonBox( "Save 4", DEFAULT_FONT, "save_4", Properties() ), 
                        ButtonBox( "Save 5", DEFAULT_FONT, "save_5", Properties() ), 
                        ButtonBox( "Save 6", DEFAULT_FONT, "save_6", Properties() ), 
                        ButtonBox( "Save 7", DEFAULT_FONT, "save_7", Properties() ), 
                        ButtonBox( "Save 8", DEFAULT_FONT, "save_8", Properties() ), 
                        ButtonBox( "Save 9", DEFAULT_FONT, "save_9", Properties() ), 
                    },
                    ContainerType::SCREEN,
                    "save",
                    {}
                ) 
            }, 
            { 
                "load" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "Return", DEFAULT_FONT, "leave",  Properties() ),
                        ButtonBox( "Load 1", DEFAULT_FONT, "load_1", Properties() ), 
                        ButtonBox( "Load 2", DEFAULT_FONT, "load_2", Properties() ), 
                        ButtonBox( "Load 3", DEFAULT_FONT, "load_3", Properties() ), 
                        ButtonBox( "Load 4", DEFAULT_FONT, "load_4", Properties() ), 
                        ButtonBox( "Load 5", DEFAULT_FONT, "load_5", Properties() ), 
                        ButtonBox( "Load 6", DEFAULT_FONT, "load_6", Properties() ), 
                        ButtonBox( "Load 7", DEFAULT_FONT, "load_7", Properties() ), 
                        ButtonBox( "Load 8", DEFAULT_FONT, "load_8", Properties() ), 
                        ButtonBox( "Load 9", DEFAULT_FONT, "load_9", Properties() ), 
                    },
                    ContainerType::SCREEN,
                    "load",
                    {}
                ) 
            }, 
            { 
                "warning" , 
                Container( 
                    {
                    },
                    { 
                        ButtonBox( "warning!!!", DEFAULT_FONT, "main", Properties() ),
                    },
                    ContainerType::SCREEN,
                    "warning",
                    {}
                ) 
            },
        };
        return true;
    }

    void MenuHandler::handleID( std::string id, Properties *container_properties, Properties *button_properties )
    {
        // Check properties
        if ( button_properties->hasProperties() )
        {
            for ( auto&& key_value : *(button_properties->getProperties()) )
            {
                switch( key_value.first )
                {
                    case PropertyType::STACKABLE:       // Dont
                        if ( key_value.second == 1 )
                            pushPriorityContainer( id );
                        return;
                    default:
                        printf("*** WARNING: Unknown Property  ( menu_handler.cpp -> handleID() )\n");
                        return;
                }
            }
        }

        if ( id == "quit")
            quit();
        else if ( id == "leave" || id == "back" )
            popContainer();
        else
        {
            printf("*** WARNING: Unimplemented event handle... Pushing container anyways ( menu_handler.cpp -> handleID() )\n");
            pushPriorityContainer( id );
        }
    }

    bool MenuHandler::handleEvent( Event *event )
    {
        printf("menu_handler recieved: %s\n", event->getID().c_str());
        return true;
    }

    void MenuHandler::render( SDL_Renderer *renderer )
    {
        if ( inContainer() )
        {
            getContainer()->render( renderer );
        }
    }

    void MenuHandler::update()
    {
        if ( inContainer() )
        {
            getContainer()->update();
        }
    }

    void MenuHandler::save()
    {

    }

    void MenuHandler::load()
    {

    }

    void MenuHandler::quit()
    {
        GameData::quitGame();
    }
};

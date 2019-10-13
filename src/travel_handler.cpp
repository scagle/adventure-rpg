#include <SDL.h>
#include <cstdlib>
#include "travel_handler.hpp"
#include "event.hpp"
#include "world.hpp"

namespace game
{
    bool TravelHandler::loadContainers() 
    {
        this->containers = 
        { 
            { 
                "home_portal",
                Container( 
                    { 
                        TextBox("Travel", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("Forest", DEFAULT_FONT, "forest", Properties()), 
                        ButtonBox("Caves", DEFAULT_FONT, "caves", Properties()), 
                        ButtonBox("Beach", DEFAULT_FONT, "beach", Properties()), 
                    },
                    ContainerType::FOOTER,
                    "home_portal",
                    {}
                )
            },
            {
                "forest_portal",
                Container( 
                    { 
                        TextBox("Aww, too scared?", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("Home", DEFAULT_FONT, "home", Properties()), 
                    },
                    ContainerType::FOOTER,
                    "forest_portal",
                    {}
                )
            },
            {
                "cave_portal",
                Container( 
                    { 
                        TextBox("Are you...", DEFAULT_FONT, Properties()),
                        TextBox("CAVING in?", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("HAHAHA yes", DEFAULT_FONT, "home", Properties()), 
                    },
                    ContainerType::FOOTER,
                    "cave_portal",
                    {}
                )
            },
            {
                "inner_cave_portal",
                Container( 
                    { 
                        TextBox("You're not ready yet...", DEFAULT_FONT, Properties()),
                        TextBox("( UNIMPLEMENTED )", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("Yeah yeah yeah...", DEFAULT_FONT, "leave", Properties()), 
                    },
                    ContainerType::FOOTER,
                    "inner_cave_portal",
                    {}
                )
            },
            {
                "beach_portal",
                Container( 
                    { 
                        TextBox("Too much sun?", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("Get me home please!", DEFAULT_FONT, "home", Properties()), 
                    },
                    ContainerType::FOOTER,
                    "beach_portal",
                    {}
                )
            },
        };
        return true;
    }

    void TravelHandler::handleID( std::string id, Properties *container_properties, Properties *button_properties )
    {
        popContainer();
        int entity = 0;
        if ( id == "home")
            entity = 0;
        if ( id == "forest")
            entity = 2;
        if ( id == "caves")
            entity = 2;
        if ( id == "beach")
            entity = 1;
        World::updateMap( id, entity ); 
    }

    bool TravelHandler::handleEvent( Event *event )
    {
        printf("travel_handler recieved: %s\n", event->getID().c_str());
        if ( event->getValue() == 1 )
        {
            if ( event->isEmitted() )
            {
                printf("Pushing container '%s' with coordinates\n", event->getID().c_str());
                pushContainer(event->getID(), event->getX(), event->getY());
            }
            else
            {
                printf("Pushing container '%s'\n", event->getID().c_str());
                pushContainer(event->getID());
            }
        }
        else
        {
            printf("Popping container '%s'\n", event->getID().c_str());
            popContainer();
        }
        return true;
    }

    void TravelHandler::render( SDL_Renderer *renderer )
    {
        if ( inContainer() )
            getContainer()->render( renderer );
    }

    void TravelHandler::update()
    {

    }
};

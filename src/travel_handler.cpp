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
                        TextBox("Travel", DEFAULT_FONT)
                    }, 
                    { 
                        ButtonBox("Forest", DEFAULT_FONT, "forest"), 
                        ButtonBox("Caves", DEFAULT_FONT, "caves"), 
                        ButtonBox("Beach", DEFAULT_FONT, "beach"), 
                    },
                    ContainerType::FOOTER,
                    "home_portal"
                )
            },
            {
                "forest_portal",
                Container( 
                    { 
                        TextBox("Aww, too scared?", DEFAULT_FONT)
                    }, 
                    { 
                        ButtonBox("Home", DEFAULT_FONT, "home"), 
                    },
                    ContainerType::FOOTER,
                    "forest_portal"
                )
            },
        };
        return true;
    }

    void TravelHandler::handleID( std::string id )
    {
        int entity = 0;
        if ( id == "home")
            entity = 0;
        if ( id == "forest")
            entity = 2;
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

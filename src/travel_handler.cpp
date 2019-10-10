#include <SDL.h>
#include <cstdlib>
#include "travel_handler.hpp"
#include "event.hpp"

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
                        ButtonBox("Forest", DEFAULT_FONT, "travel_forest"), 
                        ButtonBox("Caves", DEFAULT_FONT, "travel_caves"), 
                        ButtonBox("Beach", DEFAULT_FONT, "travel_beach"), 
                    },
                    ContainerType::FOOTER,
                    "home_portal"
                )
            },
        };
        return true;
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

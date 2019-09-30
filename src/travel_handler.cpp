#include <SDL.h>
#include <cstdlib>
#include "travel_handler.hpp"
#include "event.hpp"

namespace game
{
    bool TravelHandler::loadContainers() 
    {
        return true;
    }

    void TravelHandler::handleEvent(Event *event)
    {
        printf("travel_handler recieved: %s", event->getID().c_str());
//        switch ( event.getType() )
//        {
//            case EventType::PORTAL:
//                setEvent(EventType::PORTAL, flag);
//                if (flag)
//                    printf("In Portal!\n");
//                else
//                    printf("No Longer in Portal!\n");
//                break;
//            default:
//                printf("Unknown Event\n");
//                break;
//        }
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

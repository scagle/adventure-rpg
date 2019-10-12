#include <SDL.h>
#include <cstdio>
#include <unordered_map>
#include <stack>
#include "container_handler.hpp"

namespace game
{
    bool ContainerHandler::loadContainers()
    {
        this->containers = {};
        printf("Calling base-class function, which is empty (container_handler.cpp -> loadContainers())\n");
        return false;
    }

//// 'containers' unordered_map methods

    void ContainerHandler::moveContainer( Direction dir )
    {
        this->active_containers.back().moveCursor(dir);
    }

    void ContainerHandler::selectContainer()
    {
        std::string id = this->active_containers.back().select();
        if (id != "" && id != "text_continue")
        {
            handleID(id);
        }

        printf("Action: '%s'\n", id.c_str());
    }

    void ContainerHandler::handleID( std::string id )
    {
        popContainer();
        if ( id != "leave")
            pushPriorityContainer(id);
    }

    Container* ContainerHandler::getContainer()
    {
        if (active_containers.size() == 0)
            printf("*** Warning: No containers on stack! (ui/container_handler.cpp -> getContainer())\n");

        return &(this->active_containers.back());
    }

    std::string ContainerHandler::getContainerID()
    {
        return this->active_containers.back().getID();
    }

    bool ContainerHandler::inContainer()
    {
        return (active_containers.size() > 0);
    }

    void ContainerHandler::pushContainer( std::string id )
    {
        active_containers.push_front( containers[id] );
    }

    void ContainerHandler::pushContainer( std::string id, int x, int y )
    {
        Container emitted_container = containers[id];
        emitted_container.setEmittedPosition( x, y );
        active_containers.push_front( emitted_container );
    }

    void ContainerHandler::pushPriorityContainer( std::string id )
    {
        active_containers.push_back( containers[id] );
    }

    void ContainerHandler::popContainer()
    {
        if ( !active_containers.empty() )
            active_containers.pop_back();
    }

    void ContainerHandler::removeContainer( std::string id )  
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i].getID() )
                {
                    active_containers.erase(active_containers.begin() + i);
                }
            }
        }
    }

    bool ContainerHandler::checkContainer( std::string id )
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i].getID() )
                {
                    return true;
                }
            }
        }

        return false;
    }

//// 'active_containers' deque methods

    bool ContainerHandler::pushActiveContainer(std::string id)          // add container to beginning, if its not already active
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i].getID() )
                {
                    return false;   // There already exists that specific id in the queue, so return false
                }
            }
        }
        // Otherwise add it to active containers
        active_containers.push_front(containers[id]); 
        return false;
    }

    void ContainerHandler::render( SDL_Renderer *renderer )
    {
        if ( inContainer() )
            getContainer()->render( renderer );
    }

    void ContainerHandler::update()
    {

    }

};

//    bool ContainerHandler::prioritizeActiveContainer(std::string id)    // prioritize container by moving it to the end of the queue
//    {
//        if ( !active_containers.empty() )
//        {
//            for ( unsigned int i = 0; i < active_containers.size(); i++ )
//            {
//                if ( id == active_containers[i].getID() )
//                {
//                    active_containers.erase(active_containers.begin() + i);
//                    active_containers.push_back(containers[id]); 
//                    return true;
//                }
//            }
//        }
//        return false;
//    }
//
//    bool ContainerHandler::pushActiveContainerPriority(std::string id)  // add container to beginning, if its not already active
//    {
//        if ( !active_containers.empty() )
//        {
//            for ( unsigned int i = 0; i < active_containers.size(); i++ )
//            {
//                if ( id == active_containers[i].getID() )
//                {
//                    return false;   // There already exists that specific id in the queue, so return false
//                }
//            }
//        }
//        // Otherwise add it to active containers
//        active_containers.push_back(containers[id]); 
//        return false;
//    }


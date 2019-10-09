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

    void ContainerHandler::pushContainer( std::string id )
    {
        container_stack.push(containers[id]);
        current_container_id = id;
    }

    void ContainerHandler::pushContainer( std::string id, int x, int y )
    {
        Container emitted_container = containers[id];
        emitted_container.setEmittedPosition( x, y );
        container_stack.push(emitted_container);
        current_container_id = id;
        printf("Pushed container to %d, %d\n", x, y);
    }

    void ContainerHandler::popContainer()
    {
        container_stack.pop();
        if ( !inContainer() )
            current_container_id = "NONE";
    }

    void ContainerHandler::moveContainer( Direction dir )
    {
        this->container_stack.top().moveCursor(dir);
    }

    void ContainerHandler::selectContainer()
    {
        std::string id = this->container_stack.top().select();
        if (id != "" && id != "text_continue")
        {
            container_stack.push(containers[id]);
            current_container_id = id;
        }

        printf("Action: '%s'\n", id.c_str());
    }

    Container* ContainerHandler::getContainer()
    {
        if (container_stack.size() == 0)
            printf("*** Warning: No containers on stack! (ui/container_handler.cpp -> getContainer())\n");

        return &(this->container_stack.top());
    }

    std::string ContainerHandler::getContainerID()
    {
        return this->current_container_id;
    }

    bool ContainerHandler::inContainer()
    {
        return (container_stack.size() > 0);
    }

//// 'active_containers' deque methods

    bool ContainerHandler::pushActiveContainer(std::string id)          // add container to beginning, if its not already active
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i] )
                {
                    return false;   // There already exists that specific id in the queue, so return false
                }
            }
        }
        // Otherwise add it to active containers
        active_containers.push_front(id); 
        return false;
    }

    bool ContainerHandler::pushActiveContainerPriority(std::string id)          // add container to beginning, if its not already active
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i] )
                {
                    return false;   // There already exists that specific id in the queue, so return false
                }
            }
        }
        // Otherwise add it to active containers
        active_containers.push_back(id); 
        return false;
    }

    bool ContainerHandler::prioritizeActiveContainer(std::string id)          // add container to beginning, if its not already active
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i] )
                {
                    active_containers.erase(active_containers.begin() + i);
                    active_containers.push_back(id); 
                    return true;
                }
            }
        }
        return false;
    }

    bool ContainerHandler::checkActiveContainer()                      // check if any container is currently active
    {
        return ( active_containers.size() > 0 );
    }

    bool ContainerHandler::checkActiveContainer(std::string id)        // check if specific container is currently active
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i] )
                {
                    return true;
                }
            }
        }
        return false;
    }

    Container* ContainerHandler::removeActiveContainer(std::string id) // remove specific container, and return end
    {
        if ( !active_containers.empty() )
        {
            for ( unsigned int i = 0; i < active_containers.size(); i++ )
            {
                if ( id == active_containers[i] )
                {
                    active_containers.erase(active_containers.begin() + i);
                }
            }
        }
        if ( active_containers.empty() )
            return ( NULL );
        else
            return ( &containers[active_containers.back()] );
    }

    Container* ContainerHandler::popActiveContainer()                  // remove end container, and return new end
    {
        if ( !active_containers.empty() )
        {
            active_containers.pop_back();
        }
        if ( active_containers.empty() )
            return ( NULL );
        else
            return ( &containers[active_containers.back()] );
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

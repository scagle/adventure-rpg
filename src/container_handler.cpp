#include <SDL.h>
#include <cstdio>
#include <unordered_map>
#include <stack>
#include "character.hpp"
#include "container.hpp"
#include "container_handler.hpp"
#include "datatypes/properties.hpp"

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
        printf("Active Container size: %d\n", (int)active_containers.size());
        std::string id = this->active_containers.back().select();
        Properties* container_properties = this->active_containers.back().getProperties();
        Properties* button_properties = this->active_containers.back().getSelectedProperties();
        if (id != "" && id != "text_continue")
        {
            handleID(id, container_properties, button_properties);
        }

        printf("Action: '%s'\n", id.c_str());
    }

    void ContainerHandler::handleID( std::string id, Properties *container_properties, Properties *button_properties )
    {
        popContainer();
        if ( id != "leave" )
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

    void ContainerHandler::pushContainer( std::string id, Character* character)
    {
        // Create copy of container
        Container emitted_container = containers[id];

        // If character is not null, then align at character, otherwise align at specific position
        if ( character != nullptr )
        {
            emitted_container.setCharacter(character);
            emitted_container.setEmittedPosition( character->getEmitX(), character->getEmitY() );
        }
        else
        {
            emitted_container.setEmittedPosition( 0, 0 );
            printf("*** WARNING: Pushing floating container with NULL character (container_handler.cpp)\n");

        }
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


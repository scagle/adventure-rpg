#include "container_handler.hpp"

#include "character.hpp"
#include "container.hpp"
#include "datatypes/properties.hpp"

#include <SDL.h>

namespace game
{
    bool ContainerHandler::loadContainers()
    {
        this->containers = {};
        printf("Calling base-class function, which is empty (container_handler.cpp -> loadContainers())\n");
        return false;
    }

    void ContainerHandler::moveContainer( Direction dir )
    {
        this->active_containers.back().moveCursor(dir);
    }

    void ContainerHandler::selectContainer()
    {
        printf("Active Container size: %d %p\n", (int)active_containers.size(), &active_containers);
        if ( this->active_containers.back().hasButtonBoxes() )
        {
            std::string id = this->active_containers.back().select();
            Properties* container_properties = this->active_containers.back().getProperties();
            Properties* button_properties = this->active_containers.back().getSelectedProperties();
            if ( id != "" && id != "text_continue" )
            {
                handleID(id, container_properties, button_properties);
            }

            printf("Action: '%s'\n", id.c_str());
        }
    }

    void ContainerHandler::handleID( std::string id, Properties *container_properties, Properties *button_properties )
    {
        popContainer();
        if ( id != "leave" )
            pushPriorityContainer(id);
    }

    Container* ContainerHandler::getContainer()
    {
        if ( active_containers.size() == 0 )
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
        Container new_container = containers[id];
        active_containers.push_front( new_container );
        new_container.initializeBox( 0, 0 );
    }

    void ContainerHandler::pushContainer( std::string id, Character* character)
    {
        // Create copy of container
        Container new_container = containers[id];

        // If character is not null, then align at character, otherwise align at specific position
        if ( character != nullptr )
        {
            new_container.setCharacter(character);
            new_container.initializeBox( character->getEmitX(), character->getEmitY() );
        }
        else
        {
            new_container.setEmittedPosition( 0, 0 );
            printf("*** WARNING: Pushing floating container with NOBODY to follow  (container_handler.cpp)\n");

        }
        active_containers.push_front( new_container );
    }

    void ContainerHandler::pushContainer( std::string id, int emit_x, int emit_y )
    {
        // Create copy of container
        Container new_container = containers[id];
        new_container.initializeBox( emit_x, emit_y );
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


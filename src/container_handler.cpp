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

    void ContainerHandler::pushContainer( std::string id )
    {
        container_stack.push(containers[id]);
    }

    void ContainerHandler::pushContainer( std::string id, int x, int y )
    {
        Container emitted_container = containers[id];
        emitted_container.setEmittedPosition( x, y );
        container_stack.push(emitted_container);
        printf("Pushed container to %d, %d\n", x, y);
    }

    void ContainerHandler::popContainer()
    {
        container_stack.pop();
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
        }

        printf("Action: '%s'\n", id.c_str());
    }

    Container* ContainerHandler::getContainer()
    {
        if (container_stack.size() == 0)
            printf("*** Warning: No containers on stack! (ui/container_handler.cpp -> getContainer())\n");

        return &(this->container_stack.top());
    }

    bool ContainerHandler::inContainer()
    {
        return (container_stack.size() > 0);
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

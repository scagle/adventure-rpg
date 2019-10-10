#pragma once
#include <unordered_map>
#include <stack>
#include <string>
#include <SDL.h>
#include "container.hpp"

namespace game
{
    class ContainerHandler
    {
        protected:
        std::unordered_map< std::string, Container > containers;
        std::stack< Container > container_stack;
        std::deque< Container > active_containers;

        public:
        ContainerHandler() { }
        virtual ~ContainerHandler() { }
        
        virtual bool loadContainers();                  

        virtual void pushContainer( std::string );            // push container to beginning, if its not already active
        virtual void pushContainer( std::string, int, int );  // ^^^ with coordinates
        virtual void pushPriorityContainer( std::string id );
        virtual void popContainer();                          // remove end container, and return new end
        virtual void removeContainer( std::string );          // remove specific container, and return end
        virtual bool inContainer();                           // check if any container is currently active
        virtual bool checkContainer( std::string );           // check if specific container is currently active

        virtual void moveContainer(Direction);              
        virtual void selectContainer();                 
        virtual void handleID( std::string id );
        virtual Container* getContainer();              
        virtual std::string getContainerID();

        bool pushActiveContainer(std::string id);          // add container to beginning, if its not already active
        virtual void render( SDL_Renderer *renderer );  
        virtual void update();
    };
};

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
        std::deque< std::string > active_containers;
        std::string current_container_id = "NONE";

        public:
        ContainerHandler() { }
        virtual ~ContainerHandler() { }
        
        virtual bool loadContainers();                  

        // 'containers' unordered_map methods
        virtual void pushContainer(std::string);        
        virtual void pushContainer(std::string, int, int);        
        virtual void popContainer();                    
        virtual void moveContainer(Direction);          
        virtual void selectContainer();                 
        virtual Container* getContainer();              
        virtual std::string getContainerID();
        virtual bool inContainer();                     

        // 'active_containers' deque methods
        virtual bool pushActiveContainer(std::string);          // push container to beginning, if its not already active
        virtual bool pushActiveContainerPriority(std::string);  // push container to end, if its not already active
        virtual bool prioritizeActiveContainer(std::string);    // push container to end, if its not already active
        virtual bool checkActiveContainer();                    // check if any container is currently active
        virtual bool checkActiveContainer(std::string);         // check if specific container is currently active
        virtual Container* removeActiveContainer(std::string);  // remove specific container, and return end
        virtual Container* popActiveContainer();                // remove end container, and return new end

        virtual void render( SDL_Renderer *renderer );  
        virtual void update();
    };
};

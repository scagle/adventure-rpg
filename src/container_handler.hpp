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
        static std::unordered_map< std::string, Container > containers;
        static std::stack< Container* > container_stack;

        public:
        ContainerHandler() { }
        virtual ~ContainerHandler() { }
        
        virtual bool loadContainers();                  
        virtual void pushContainer(std::string);        
        virtual void popContainer();                    
        virtual void moveContainer(Direction);          
        virtual void selectContainer();                 
        virtual Container* getContainer();              
        virtual bool inContainer();                     
        virtual void render( SDL_Renderer *renderer );  
        virtual void update();
    };
};

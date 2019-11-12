#pragma once

// Forward Declarations
namespace game
{
    class Properties;
};
class SDL_Renderer;

#include "container.hpp"

#include <unordered_map>
#include <stack>
#include <deque>
#include <string>

namespace game
{
    class ContainerHandler
    {
        protected:
            std::unordered_map< std::string, Container > containers;
            std::deque< Container > active_containers;

        public:
            ContainerHandler() { }
            virtual ~ContainerHandler() { }
            
            virtual bool loadContainers();                  

            virtual void pushContainer( std::string );              // push container to beginning, if its not already active
            virtual void pushContainer( std::string, Character* );  // ^^^ with follower
            virtual void pushContainer( std::string, int, int );    // ^^^ with coordinates
            virtual void pushPriorityContainer( std::string id );   // push container to front of queue (used commonly for transitions)
            virtual void popContainer();                            // remove end container, and return new end
            virtual void removeContainer( std::string );            // remove specific container, and return end
            virtual bool inContainer();                             // check if any container is currently active
            virtual bool checkContainer( std::string );             // check if specific container is currently active

            virtual void moveContainer(Direction);                  // move button selection in a direction
            virtual void selectContainer();                         // handle selection logic when enter is pressed
            virtual void handleID( std::string id, Properties* container_properties, Properties* button_properties);
            virtual Container* getContainer();                      
            virtual std::string getContainerID();

            virtual void render( SDL_Renderer *renderer );  
            virtual void update();
    };
};

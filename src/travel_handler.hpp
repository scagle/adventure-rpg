#pragma once

// Forward Declarations
namespace game
{
    class Event;
};
class SDL_Renderer;

#include "container_handler.hpp"

namespace game
{
    class TravelHandler : public ContainerHandler
    {
        private:

        public:
            TravelHandler() { }
            virtual ~TravelHandler() { }

            bool loadContainers() override; 
            void handleID( std::string, Properties*, Properties* ) override;
            bool handleEvent( Event * );
            virtual void render( SDL_Renderer *renderer );
            virtual void update();
    };
};

#pragma once
#include <SDL.h>
#include "event.hpp"
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
        void handleID( std::string id, Properties* properties ) override;
        bool handleEvent( Event * );
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
    };
};

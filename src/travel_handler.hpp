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
        void handleEvent( Event * );
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
//        static bool inTravel() { return (container_stack.size() != 0) ; }
    };
};

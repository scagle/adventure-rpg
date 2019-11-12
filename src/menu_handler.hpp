#pragma once

// Forward Declaration 
namespace game
{
    class Event;
};
class SDL_Renderer;

#include "container_handler.hpp"

namespace game
{
    class MenuHandler : public ContainerHandler
    {
        private:

        public:
            MenuHandler() { }
            virtual ~MenuHandler() { }

            bool loadContainers() override; 
            void handleID( std::string, Properties*, Properties* ) override;
            bool handleEvent( Event * );
            virtual void render( SDL_Renderer *renderer );
            virtual void update();
            void save();
            void load();
            void quit();
    };
};

#pragma once

// Forward Declaration inside game
namespace game
{
    class Event;
};

#include "container_handler.hpp"

#include <set>
#include <string>

namespace game
{
    class DialogHandler : public ContainerHandler
    {
        private:
            static std::set< std::string > dialog_set;

        public:
            DialogHandler() { }
            virtual ~DialogHandler() { }

            bool loadContainers() override;
            void handleID( std::string, Properties*, Properties* ) override;
            bool handleEvent( Event * );
            virtual void render( SDL_Renderer *renderer );  
            virtual void update();
    };
};

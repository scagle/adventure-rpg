#pragma once
#include <set>
#include <string>
#include "container_handler.hpp"
#include "event.hpp"

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

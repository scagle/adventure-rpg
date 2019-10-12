#pragma once
#include <unordered_map>
#include <set>
#include <stack>
#include <vector>
#include "menu.hpp"
#include "event.hpp"
#include "dialog.hpp"
#include "container_handler.hpp"
#include "enums/direction.hpp"

namespace game
{
    class MenuHandler : public ContainerHandler
    {
        private:

        public:
        MenuHandler() { }
        virtual ~MenuHandler() { }

        bool loadContainers() override; 
        void handleID( std::string id, Properties* properties ) override;
        bool handleEvent( Event * );
        virtual void render( SDL_Renderer *renderer );
        virtual void update();
        void save();
        void load();
        void quit();
    };
};

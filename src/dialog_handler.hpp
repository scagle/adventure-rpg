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
//        static bool inDialog() { return (container_stack.size() != 0) ; }
        void handleEvent( Event * );
        void pushContainerToPosition(std::string id, int entity_center_x, int entity_center_y);
    };
};

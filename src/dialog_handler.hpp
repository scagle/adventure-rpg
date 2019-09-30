#pragma once
#include <string>

namespace game
{
    class DialogHandler
    {
        private:
        static std::set< std::string > dialog_set;

        public:

        DialogHandler() { }
        virtual ~DialogHandler() { }

        void pushContainerToPosition(std::string id, int entity_center_x, int entity_center_y);
    };
};

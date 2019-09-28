#include "dialog_handler.hpp"

namespace game
{
    bool MenuHandler::initContainers()
    {
        /*! TODO: Could be made more efficient by passing by reference instead of value
         *  \todo Could be made more efficient by passing by reference instead of value
         */
/////// DIALOGS /////////////////////////////////////////////////////////////////////////////////////////////////

        this->containers = 
        { 
            { 
                "portal_to_forest" ,    // id
                Container(              // Container
                    { 
                        "Travel to Forest?", 
                    }, 
                    { 
                        Container::Choice{"Yes", "travel_forest"}, 
                        Container::Choice{"No", "leave"}, 
                    }
                )
            },
            { 
                "home_merchant" ,       // id
                Container(              // Container
                    { 
                        "Hello there adventurer! Would you like to browse my wares?",
                    }, 
                    { 
                        Container::Choice{"Buy", "shop0_buy"}, 
                        Container::Choice{"Sell", "shop0_sell"}, 
                        Container::Choice{"BEGONE!", "leave"},
                    }
                )
                
            }
        };

        return true;
    }
};

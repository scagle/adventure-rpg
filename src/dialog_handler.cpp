#include "dialog_handler.hpp"
#include <string>

namespace game
{
    void DialogHandler::pushContainerToPosition(std::string id, int entity_center_x, int entity_center_y)
    {
//        dialogs[id].setAnchor(entity_center_x, entity_center_y);
//        dialog_stack.push(&dialogs[id]);
    }

    void DialogHandler::loadContainers()
    {
        this->dialogs = 
        { 
            { 
                "portal_to_forest" , 
                Dialog( 
                    { 
                        "Travel to Forest?", 
                    }, 
                    { 
                        Dialog::Choice{"Yes", "travel_forest"}, 
                        Dialog::Choice{"No", "leave"}, 
                    }
                )
            },
            { 
                "home_merchant" , 
                Dialog( 
                    { 
                        "Hello there adventurer! Would you like to browse my wares?",
                    }, 
                    { 
                        Dialog::Choice{"Buy", "shop0_buy"}, 
                        Dialog::Choice{"Sell", "shop0_sell"}, 
                        Dialog::Choice{"BEGONE!", "leave"},
                    }
                )
                
            }
        };
    }
};

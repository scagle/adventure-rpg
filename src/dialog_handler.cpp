#include <string>
#include "dialog_handler.hpp"
#include "container.hpp"
#include "button_box.hpp"
#include "button_box.hpp"
#include "globals.hpp"

namespace game
{
    std::set< std::string > DialogHandler::dialog_set;
    bool DialogHandler::loadContainers() 
    {
        this->containers = 
        { 
            { 
                "main_portal",
                Container( 
                    { 
                        TextBox("Travel to Forest?", DEFAULT_FONT)
                    }, 
                    { 
                        ButtonBox("Yes", DEFAULT_FONT, "travel_forest"), 
                        ButtonBox("No", DEFAULT_FONT, "leave"), 
                    }
                )
            },
            { 
                "merchant0",
                Container( 
                    { 
                        TextBox("Hello there adventurer! Would you like to browse my wares?", DEFAULT_FONT)
                    }, 
                    { 
                        ButtonBox("Buy", DEFAULT_FONT, "shop0_buy"), 
                        ButtonBox("Sell", DEFAULT_FONT, "shop0_sell"), 
                        ButtonBox("BEGONE!", DEFAULT_FONT, "leave"),
                    }
                )
            }
        };
        return true;
    }

    void DialogHandler::pushContainerToPosition(std::string id, int entity_center_x, int entity_center_y)
    {
//        containers[id].setAnchor(entity_center_x, entity_center_y);
//        dialog_stack.push(&containers[id]);
    }

    void DialogHandler::handleEvent(Event *event)
    {
        printf("dialog_handler recieved: %s", event->getID().c_str());
//        switch ( event.getType() )
//        {
//            case EventType::PORTAL:
//                setEvent(EventType::PORTAL, flag);
//                if (flag)
//                    printf("In Portal!\n");
//                else
//                    printf("No Longer in Portal!\n");
//                break;
//            default:
//                printf("Unknown Event\n");
//                break;
//        }
    }

};

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
                "home_merchant0",
                Container( 
                    { 
                        TextBox("Hello there", DEFAULT_FONT),
                        TextBox("adventurer!", DEFAULT_FONT),
                        TextBox("Would you like", DEFAULT_FONT),
                        TextBox("to browse my wares?", DEFAULT_FONT),
                    }, 
                    { 
                        ButtonBox("Buy", DEFAULT_FONT, "shop0_buy"), 
                        ButtonBox("Sell", DEFAULT_FONT, "shop0_sell"), 
                        ButtonBox("BEGONE!", DEFAULT_FONT, "leave"),
                    },
                    ContainerType::FLOATING
                )
            },
            { 
                "home_npc0",
                Container( 
                    { 
                        TextBox("OMG!", DEFAULT_FONT),
                        TextBox("I'm so bored...", DEFAULT_FONT),
                        TextBox("There's NOTHING here!", DEFAULT_FONT),
                    }, 
                    { 
                        ButtonBox("Go away!", DEFAULT_FONT, "leave"),
                    },
                    ContainerType::FLOATING
                )
            },
        };
        return true;
    }

    bool DialogHandler::handleEvent( Event *event )
    {
        // TODO: Figure out how to have multiple active dialogs simutaneously
        std::string id = event->getID();
        int value = event->getValue();
        if ( value == 1 )
        {
            if ( event->isEmitted() )
            {
                pushContainer(id, event->getX(), event->getY());
            }
            else
            {
                pushContainer(id);
            }
        }
        else
        {
            popContainer();
        }
        return true;
    }

    void DialogHandler::render( SDL_Renderer *renderer )
    {
        if ( inContainer() )
            getContainer()->render( renderer );
    }

    void DialogHandler::update()
    {

    }

};

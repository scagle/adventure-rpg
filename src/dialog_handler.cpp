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
                "merchant0",
                Container( 
                    { 
                        TextBox("Hello", DEFAULT_FONT),
                        TextBox("there adventurer!", DEFAULT_FONT),
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
        };
        return true;
    }

    bool DialogHandler::handleEvent( Event *event )
    {
        // TODO: Figure out how to have multiple active dialogs simutaneously
        if ( event->getValue() == 1 )
        {
            if ( event->isEmitted() )
            {
                pushContainer(event->getID(), event->getX(), event->getY());
            }
            else
            {
                pushContainer(event->getID());
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

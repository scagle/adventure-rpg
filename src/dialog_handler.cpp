#include "dialog_handler.hpp"

#include "container.hpp"
#include "text_box.hpp"
#include "button_box.hpp"
#include "datatypes/properties.hpp"
#include "event.hpp"

#include "enums/property_type.hpp"
#include "globals.hpp"

#include <string>
#include <vector>

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
                        TextBox("Hello there adventurer!", DEFAULT_FONT, Properties()),
                        TextBox("Would you like to browse my wares?", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("Buy", DEFAULT_FONT, "shop0_buy", Properties()), 
                        ButtonBox("Sell", DEFAULT_FONT, "shop0_sell", Properties()), 
                        ButtonBox("BEGONE!", DEFAULT_FONT, "leave", Properties()),
                    },
                    ContainerType::FLOATING,
                    "home_merchant0",
                    Properties()
                )
            },
            { 
                "home_npc0",
                Container( 
                    { 
                        TextBox("OMG! I'm so freaking bored!!!", DEFAULT_FONT, Properties()),
                        TextBox("There's like literally NOTHING to do here!", DEFAULT_FONT, Properties()),
                        TextBox("Like what the heck was the creator thinking?", DEFAULT_FONT, Properties()),
                        TextBox("Or is he even thinking at all?", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("SAVAGE!", DEFAULT_FONT, "leave", Properties()),
                        ButtonBox("Okay...", DEFAULT_FONT, "leave", Properties()),
                        ButtonBox("Go away!", DEFAULT_FONT, "leave", Properties()),
                    },
                    ContainerType::FLOATING,
                    "home_npc0",
                    Properties()
                )
            },
            { 
                "forest_wizard",
                Container( 
                    { 
                        TextBox("Oh hi! You really scared me!\nI was just practicing my wizard spells.", DEFAULT_FONT, Properties()),
                        TextBox("Would you be interested in being my test dummy?", DEFAULT_FONT, Properties()),
                    }, 
                    { 
                        ButtonBox("Cast Away!", DEFAULT_FONT, "", Properties()),
                        ButtonBox("Umm... No.", DEFAULT_FONT, "leave", Properties()),
                    },
                    ContainerType::FLOATING,
                    "forest_wizard",
                    Properties()
                )
            },
            { 
                "scared_ferret",
                Container( 
                    { 
                        TextBox( "*SQUEAK*", DEFAULT_FONT, Properties() ),
                    }, 
                    { 

                    },
                    ContainerType::FLOATING,
                    "scared_ferret",
                    Properties( { { PropertyType::NO_PROMPT, 1 }, { PropertyType::SIZE, 30 } } )
                )
            },
            { 
                "ogre",
                Container( 
                    { 
                        TextBox( "GET EN MY BELLEH!", DEFAULT_FONT, Properties() ),
                    }, 
                    { 

                    },
                    ContainerType::FLOATING,
                    "scared_ferret",
                    Properties( { { PropertyType::NO_PROMPT, 1 }, { PropertyType::SIZE, 200 } } )
                )
            },
        };
        return true;
    }

    void DialogHandler::handleID( std::string id, Properties *container_properties, Properties *button_properties )
    {
        // Check button properties
        //if ( button_properties->hasProperties() )
        //{
        //    for ( auto&& key_value : *(button_properties->getProperties()) )
        //    {
        //        switch( key_value.first )
        //        {
        //            case PropertyType::STACKABLE:       
        //                if ( key_value.second == 1 )
        //                    pushPriorityContainer( id );
        //                return;
        //            default:
        //                printf("*** WARNING: Unknown Property  ( menu_handler.cpp -> handleID() )\n");
        //                return;
        //        }
        //    }
        //}

        if ( id == "leave" || id == "back" )
            popContainer();
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
                pushContainer(id, event->getCharacter());
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
        if ( inContainer() )
            getContainer()->update();
    }
};

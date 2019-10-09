#pragma once

namespace game
{
    enum class ContainerOrientation
    {
        VERTICAL,
        HORIZONTAL,
    };
    enum class ContainerType
    {
        FLOATING , // floating at a postition (IE: dialogs)
        SCREEN   , // covers entire screen (IE: main menu)
        FOOTER   , // covers bottom of screen (IE: travel menu)
    };

    enum class ContainerID
    {
        // Menus
        MAIN , 
        SAVE , 
        LOAD , 
        WARNING , 
        QUIT ,

        // Dialogs
        HOME_MERCHANT0 ,
        HOME_NPC0 ,

        // Travels
        HOME_PORTAL ,

        // Misc.
        TEXT_CONTINUE ,
    };
};

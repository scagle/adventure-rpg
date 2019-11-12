#pragma once

namespace game
{
    enum class ContainerType
    {
        FLOATING , // floating at a postition (IE: dialogs)
        SCREEN   , // covers entire screen (IE: main menu)
        FOOTER   , // covers bottom of screen (IE: travel menu)
    };
};

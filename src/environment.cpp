#include "environment.hpp"
#include <SDL.h>

namespace game
{
    /*! TODO: Figure out why for ( element : array ) loops were causing "off by 16" errors when placed here
     *  \todo Figure out why for ( element : array ) loops were causing "off by 16" errors when placed here
     */
    void Environment::render( SDL_Renderer *renderer ) 
    {
        //printf("render: this: %p, vec_portal: %p portal: %p\n", this, getPortals(), &getPortals()[0]);
        for (unsigned int i = 0; i < portals.size(); i++)
            portals[i].render( renderer );
        for (unsigned int i = 0; i < solids.size(); i++)
            solids[i].render( renderer );
        for (unsigned int i = 0; i < characters.size(); i++)
            characters[i].render( renderer );

        for (Character chr : (*getCharacters()))
            chr.render( renderer );
    }

    void Environment::update() 
    {
        //printf("update: this: %p, vec_portal: %p portal: %p\n", this, getPortals(), &getPortals()[0]);
        for (unsigned int i = 0; i < solids.size(); i++)
            solids[i].update();
        for (unsigned int i = 0; i < portals.size(); i++)
            portals[i].update();
        for (unsigned int i = 0; i < characters.size(); i++)
            characters[i].update();
    }
};

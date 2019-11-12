// Forward Declarations
namespace game
{
    class Solid;
    class Character;
    class DynamicCharacter;
};
class SDL_Renderer;

#include "environment.hpp"

namespace game
{
    /*! TODO: Figure out why for ( element : array ) loops were causing "off by 16" errors when placed here
     *  \todo Figure out why for ( element : array ) loops were causing "off by 16" errors when placed here
     */
    void Environment::render( SDL_Renderer *renderer ) 
    {
        for ( unsigned int i = 0; i < portals.size(); i++ )
            portals[i].render( renderer );
        for ( unsigned int i = 0; i < solids.size(); i++ )
            solids[i].render( renderer );
        for ( unsigned int i = 0; i < characters.size(); i++ )
            characters[i].render( renderer );
        for (unsigned int i = 0; i < dynamics.size(); i++)
            dynamics[i].render( renderer );

        for ( Character chr : (*getCharacters()) )
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
        for (unsigned int i = 0; i < dynamics.size(); i++)
            dynamics[i].update();
    }
};

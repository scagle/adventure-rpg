#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SDL.h>
#include "world.hpp"
#include "solid.hpp"
#include "character.hpp"
#include "globals.hpp"

using namespace std;

namespace game
{
    
    std::vector< Environment > World::maps;
    unsigned int World::current_map = 0;

    World::World()
    {
        loadMaps();
    }

    bool World::loadMaps()
    {

        bool success = true;
        vector< Solid > map0_objects = { 
            // SOLIDS (Collisions)
            Solid( { 50, 50, 100, 2 },  { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 150, 50, 2, 380 }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 152, 428, 20, 2 }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 172, 40, 2, 380 }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            // Top Edge(s)
            Solid( { 10, 10, (SCREEN_WIDTH-80) / 2, 2 }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 10 + (SCREEN_WIDTH-80) / 2 + 60, 10, (SCREEN_WIDTH-80) / 2, 2 }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            // Right Edge(s)
            Solid( { SCREEN_WIDTH - 12, 10, 2, (SCREEN_HEIGHT - 20) }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            // Bottom Edge(s)
            Solid( { 10, SCREEN_HEIGHT - 12, (SCREEN_WIDTH - 20), 2 }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
            // Left Edge(s)
            Solid( { 10, 10, 2, (SCREEN_HEIGHT - 20) }, { 50, 50, 50, 255 }, Solid::Type::SOLID ),
        };

        vector< Solid > map0_portals = { 
            // Portal(s)
            Solid( { 10 + (SCREEN_WIDTH-80) / 2, 0, 60, 40}, { 255, 255, 200, 255 }, Solid::Type::PORTAL, "forest" ), 
        };

        vector< Character > map0_characters = { 
            Character( {250, 400, 20, 20}, { 100, 50, 22, 255 }, "Sally", false, "home_merchant" ),
            Character( {400, 250, 20, 20}, { 200, 50, 22, 255 }, "Richard", false ),
        };

        maps.push_back(Environment("home", map0_objects, map0_portals, map0_characters));

        return success;
    }

    void World::render( SDL_Renderer *renderer ) 
    {
        getCurrentMap()->render( renderer );
    }

    void World::update() 
    {

        getCurrentMap()->update();
    }

    std::vector< Character* >* World::getCharacters()
    {
        std::vector< Character* >* all_characters = new std::vector< Character* >;
        /*! TODO: This
         *  \todo This
         */
        printf("*** WARNING: unimplemented/todo code @(world.cpp -> getCharacters())\n");

        return all_characters;
    }

    // Get files with "name" in it
    vector< string > World::getFiles( string dir, string name )
    {
        /*! TODO: Finish this with some good ole' cross platform string globbing
         *  \todo Finish this with some good ole' cross platform string globbing
         */
        vector< string > files;
        return files;
    }
};

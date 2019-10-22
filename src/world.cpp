#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SDL.h>
#include "world.hpp"
#include "solid.hpp"
#include "main_character.hpp"
#include "character.hpp"
#include "dynamic_character.hpp"
#include "globals.hpp"
#include "datatypes/position.hpp"

using std::vector;
using std::string;

namespace game
{
    
    std::unordered_map< std::string, Environment > World::maps;
    Environment* World::current_map = &(maps["home"]);
    MainCharacter World::main_character;

    World::World()
    {
        main_character = MainCharacter( SDL_Rect{15, 50, 20, 20}, SDL_Color{255, 50, 50, 255}, MAIN_CHARACTER_NAME );
        loadMaps();
    }

    bool World::loadMaps()
    {

        bool success = true;
        // Default Entry Points for maps
        std::vector< Position > default_entries = { Position( 310, 50 ), Position( 50, 230 ), Position( 310, 410 ), Position( 570, 170 ) };

/////// Home
        SDL_Color home_background = { 255, 255, 225, 255 };
    
        vector< Solid > home_objects = { 
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

        vector< Solid > home_portals = { 
            // Portal(s)
            Solid( { 10 + (SCREEN_WIDTH-80) / 2, 0, 60, 40}, { 255, 255, 200, 255 }, Solid::Type::PORTAL, "home_portal" ), 
        };

        vector< Character > home_characters = { 
            Character( {350, 400, 20, 20}, { 100, 50, 22, 255 }, "Sally", "home_merchant0" ),
            Character( {400, 350, 20, 20}, { 200, 50, 22, 255 }, "Richard", "home_npc0" ),
        };

        vector< DynamicCharacter > home_dynamics = { 
            DynamicCharacter( {50, 400, 20, 20}, { 150, 100, 22, 255 }, "Crazy Ed", DynamicCharacter::Behavior::RANDOM),
        };

/////// Forest 
        SDL_Color forest_background = { 87, 45, 9, 255 };

        vector< Solid > forest_objects = { 
            Solid( { 70, 70, 30, 30 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 75, 75, 20, 20 }, { 50, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 80, 80, 10, 10 }, { 50, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 128, 50, 35, 35 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 133, 55, 25, 25 }, { 50, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 138, 60, 15, 15 }, { 50, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 340, 340, 30, 30 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 345, 345, 20, 20 }, { 50, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 350, 350, 10, 10 }, { 50, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 500, 100, 50, 50 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 505, 105, 40, 40 }, { 50, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 510, 110, 30, 30 }, { 50, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 220, 300, 100, 100 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 225, 305, 90, 90 }, { 50, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 230, 310, 80, 80 }, { 50, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 500, 340, 40, 40 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 505, 345, 30, 30 }, { 50, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 510, 350, 20, 20 }, { 50, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 450,   0, 100, 100 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 455,   5,  90,  90 }, { 40, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 460,  10,  80,  80 }, { 30, 255, 50, 255 }, Solid::Type::SOLID ),

            Solid( { 0,   400, 100, 100 }, { 50, 200, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 5,   405,  90,  90 }, { 40, 225, 50, 255 }, Solid::Type::SOLID ),
            Solid( { 10,  410,  80,  80 }, { 30, 255, 50, 255 }, Solid::Type::SOLID ),
        };

        vector< Solid > forest_portals = { 
            // Portal(s)
            Solid( { 10 + (SCREEN_WIDTH-80) / 2, SCREEN_HEIGHT-40 , 60, 40}, { 255, 255, 200, 255 }, Solid::Type::PORTAL, "forest_portal" ), 
        };

        vector< Character > forest_characters = { 
            Character( {200, 230, 20, 20}, { 50, 150, 50, 255 }, "Wilson the Wizard", "forest_wizard" ),
        };

        vector< DynamicCharacter > forest_dynamics = { 
            DynamicCharacter( {300, 200, 10, 10}, { 255, 50, 22, 255 }, "Frightened Ferret", DynamicCharacter::Behavior::LOCAL_FLEE),
        };

/////// Caves
        SDL_Color caves_background = { 70, 60, 20, 255 };

        vector< Solid > caves_objects = { 
            Solid( { 0   , 0 , 50  , 480 } , { 137 , 87 , 60 , 255 } , Solid::Type::SOLID ) ,
            Solid( { 100 , 0 , 540 , 100 } , { 137 , 87 , 60 , 255 } , Solid::Type::SOLID ) ,
            Solid( { 590 , 0 , 50  , 480 } , { 137 , 87 , 60 , 255 } , Solid::Type::SOLID ) ,
        };

        vector< Solid > caves_portals = { 
            // Portal(s)
            Solid( { SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 40, 60, 40 }, { 255, 255, 200, 255 }, Solid::Type::PORTAL, "cave_portal" ), 
            Solid( { 50, 0, 50, 40 }, { 255, 255, 200, 255 }, Solid::Type::PORTAL, "inner_cave_portal" ), 
        };

        vector< Character > caves_characters = { 

        };

        vector< DynamicCharacter > caves_dynamics = { 
            DynamicCharacter( {250, 150, 50, 50}, { 50, 200, 50, 255 }, "Goblin", DynamicCharacter::Behavior::GLOBAL_FOLLOW),
        };

/////// Beach
        SDL_Color beach_background = { 245, 204, 77, 255 };

        vector< Solid > beach_objects = { 
            Solid( { 500, 0, 200, 480 }, { 80, 100, 255, 255 }, Solid::Type::SOLID ),
        };

        vector< Solid > beach_portals = { 
            // Portal(s)
            Solid( { 0, SCREEN_HEIGHT / 2 - 30, 40, 60}, { 255, 255, 200, 255 }, Solid::Type::PORTAL, "beach_portal" ), 
        };

        vector< Character > beach_characters = { 

        };

        vector< DynamicCharacter > beach_dynamics = { 
        };

        maps["home"] = Environment("home", home_background, home_objects, home_portals, home_characters, home_dynamics, default_entries);
        maps["forest"] = Environment("forest", forest_background, forest_objects, forest_portals, forest_characters, forest_dynamics, default_entries);
        maps["caves"] = Environment("caves", caves_background, caves_objects, caves_portals, caves_characters, caves_dynamics, default_entries);
        maps["beach"] = Environment("beach", beach_background, beach_objects, beach_portals, beach_characters, beach_dynamics, default_entries);

        return success;
    }

    void World::updateMap( std::string id, int entry )
    {
        if ( maps.count( id ) == 0 )
        {
            printf( "*** WARNING: '%s' does not name a valid map\n", id.c_str() );
            return;
        }
        current_map = &(maps[id]);
        main_character.setPosition( current_map->getEntry( entry ) );
        printf( "Traveling to '%s'\n", id.c_str() );
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
        /*! TODO: Finish this with some good cross platform globbing
         *  \todo Finish this with some good cross platform globbing
         */
        vector< string > files;
        return files;
    }

    void World::setMainCharacterVelocity( float velocity_x, float velocity_y ) 
    {
        main_character.setVelocity(velocity_x, velocity_y);
    }

    void World::render( SDL_Renderer *renderer ) 
    {
        getCurrentMap()->render( renderer );
        main_character.render( renderer );
    }

    void World::update() 
    {
        main_character.update();
        getCurrentMap()->update();
    }
};

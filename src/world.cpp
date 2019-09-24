#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "world.hpp"
#include "solid.hpp"

using namespace std;

namespace game
{
    World::World()
    {
        loadMaps();
    }

    bool World::loadMaps()
    {

        bool success = true;
        vector< Solid > map0 = { Solid( {50, 50, 100, 2}, {50, 50, 50} ) };
        maps.push_back(Environment(map0));

    // TODO
    //    //vector< string > files = getFiles("../assets/", ".map");
    //
    //    string line;
    //    ifstream map_stream( "../assets/home.gamemap" );
    //    if ( map_stream.is_open() )
    //    {
    //        while ( getline( map_stream, line ) )
    //        {
    //            cout << line << "\n";
    //        }
    //        map_stream.close();
    //    }
    //    else
    //    {
    //        cout << "Couldn't find ../assets/home.map (objects/world.cpp -> loadMaps())" << "\n";
    //        success = false;
    //    }
        return success;
    }

    // Get files with "name" in it
    vector< string > World::getFiles(string dir, string name)
    {
        /*! TODO: Finish this with some good ole' cross platform string globbing
         *  \todo Finish this with some good ole' cross platform string globbing
         */
        vector< string > files;
        return files;
    }
}

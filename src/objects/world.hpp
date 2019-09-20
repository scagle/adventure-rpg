#pragma once
#include <vector>
#include <string>
#include "environment.hpp"
#include "character.hpp"

// World is used to keep track of all the different maps, and variables 
// associated with the story
class World
{
    private:
    std::vector< Environment > maps;
    unsigned int current_map = 0;   

    public:
    World();
    bool loadMaps(); 
    std::vector< std::string > getFiles(std::string, std::string); 
    Environment* getCurrentMap() { return &(this->maps[current_map]); }
    Environment* getMap(unsigned int index) { return &(this->maps[index]); }

    std::vector< Character* >& getCharacters(); // TODO: Recursively check all environements and return characters
    
};

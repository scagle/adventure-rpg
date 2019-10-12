#pragma once
#include <vector>
#include <string>

namespace game
{
    class Properties
    {
        private:
        std::vector< std::pair< std::string, int > > properties;

        public:
        Properties() { }
        Properties( std::vector< std::pair< std::string, int > > p ) : properties(p) { }
        virtual ~Properties() { }

        std::vector< std::pair< std::string, int > >* getProperties() { return &(this->properties); }
        bool hasProperties() { return ( this->properties.size() > 0 ); }
//        std::vector< std::string > getKeys();
//        std::vector< int > getValues();
    };
};

#pragma once
#include <vector>
#include <string>
#include "../enums/property_type.hpp"

namespace game
{
    class Properties
    {
        private:
        std::vector< std::pair< PropertyType, int > > properties;

        public:
        Properties() { }
        Properties( std::vector< std::pair< PropertyType, int > > p ) : properties(p) { }
        virtual ~Properties() { }

        std::vector< std::pair< PropertyType, int > >* getProperties() { return &(this->properties); }
        bool hasProperties() { return ( this->properties.size() > 0 ); }
//        std::vector< std::string > getKeys();
//        std::vector< int > getValues();
    };
};

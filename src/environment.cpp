#include "environment.hpp"

namespace game
{
    Environment::Environment()
    {

    }

    Environment::Environment(std::vector< Solid >& solids)
    { 
        this->solids = solids; 
    }
}

#include "environment.hpp"

Environment::Environment()
{

}

Environment::Environment(std::vector< Solid >& solids)
{ 
    this->solids = solids; 
}

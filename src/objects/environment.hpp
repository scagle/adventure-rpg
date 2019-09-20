#pragma once

#include <vector>
#include "solid.hpp"
#include "character.hpp"

class Environment
{
    private:
    std::vector< Solid > solids;
    std::vector< Character > characters;

    public:
    Environment();
    Environment(std::vector< Solid >& solids);
    std::vector< Solid > getSolids() { return this->solids; }
};

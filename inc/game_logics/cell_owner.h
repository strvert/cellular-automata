#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>

#include "game_logics/cell_base.h"

class CellOwner
{
public:
    using CoordValueType = uint64_t;
    using CoordVector = sf::Vector2<CoordValueType>;

public:
    ~CellOwner() {}
    virtual const CellBase& getNeighbCell(const CoordVector coord,
                                          NeighbPos pos) const = 0;
    virtual const CellBase& getCell(const CoordVector coord) const
    {
        return getNeighbCell(coord, NeighbPos::C);
    }
};

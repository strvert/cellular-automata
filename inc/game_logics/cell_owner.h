#pragma once

#include <cstdint>

#include "game_logics/cell_base.h"

class CellOwner
{
public:
    ~CellOwner() {}
    virtual const CellBase& getNeighbCell(const uint64_t idx, NeighbPos pos) const = 0;
    virtual const CellBase& getCell(const uint64_t idx) const {
        return getNeighbCell(idx, NeighbPos::C);
    }
};

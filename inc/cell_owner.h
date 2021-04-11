#pragma once

#include <cstdint>

#include "cell_base.h"

class cell_owner
{
public:
    ~cell_owner() {}
    virtual const cell_base& get_neighb_cell(const uint64_t idx, neighb_pos pos) const = 0;
    virtual const cell_base& get_cell(const uint64_t idx) const {
        return get_neighb_cell(idx, neighb_pos::C);
    }
};

#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <vector>

#include "chunk.h"
#include "lifegame_cell.h"

class field : public cell_owner
{
private:
    const uint32_t x_cell_count;
    const uint32_t y_cell_count;

    chunk chunk;

public:
    field(const uint32_t x_cell_count, const uint32_t y_cell_count)
      : x_cell_count(x_cell_count)
      , y_cell_count(y_cell_count)
      , chunk(sf::Vector2u(x_cell_count, y_cell_count), 0, *this)
    {}

    uint32_t get_x_cell_count() const { return x_cell_count; }
    uint32_t get_y_cell_count() const { return y_cell_count; }

    const cell_base& get_neighb_cell(const uint64_t idx, neighb_pos pos) const
    {}
    const cell_base& get_cell(const uint64_t idx) const
    {
        return get_neighb_cell(idx, neighb_pos::C);
    }

    void update() {}
};

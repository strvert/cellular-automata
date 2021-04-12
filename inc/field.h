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
    sf::Vector2u field_size;

    chunk chunk;

public:
    field(const sf::Vector2u field_size)
      : field_size(field_size)
      , chunk(field_size, 0, *this)
    {}

    uint32_t get_x_cell_count() const { return field_size.x; }
    uint32_t get_y_cell_count() const { return field_size.y; }

    const cell_base& get_neighb_cell(const uint64_t idx, neighb_pos pos) const
    {

    }
    const cell_base& get_cell(const uint64_t idx) const
    {
        return get_neighb_cell(idx, neighb_pos::C);
    }

    void update() {}
};

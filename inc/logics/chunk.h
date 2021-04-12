#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "logics/cell_owner.h"
#include "logics/lifegame_cell.h"

class cell_base;

class chunk : public cell_owner
{
private:
    const field& owner_field;
    const uint64_t chunk_id;

    const sf::Vector2u chunk_size;

    std::vector<std::unique_ptr<cell_base>> cells;

public:
    ~chunk() {}

    chunk(const sf::Vector2u chunk_size, const uint64_t id, const field& pf)
      : owner_field(pf)
      , chunk_id(id)
      , chunk_size(chunk_size)
    {
        const auto cell_count = get_cell_count();
        cells.reserve(cell_count);
        for (auto idx = 0; idx < cell_count; idx++)
        {
            cells.push_back(std::make_unique<lifegame_cell>(*this, idx));
            cells[idx]->set_state(idx % 2);
        }
    }

    virtual const cell_base& get_neighb_cell(const uint64_t idx,
                                             neighb_pos pos) const override
    {
        switch (pos)
        {
            case neighb_pos::C: return *(cells[idx]);
            case neighb_pos::N:
            case neighb_pos::NE: break;
            case neighb_pos::E: return *(cells[idx + 1]);
            case neighb_pos::SE: break;
            case neighb_pos::S: break;
            case neighb_pos::SW: break;
            case neighb_pos::W: return *(cells[idx + 1]);
            case neighb_pos::NW: break;
        };
    }

    uint64_t get_cell_count() const { return chunk_size.x * chunk_size.y; }
};

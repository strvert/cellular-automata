#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "logics/cell_owner.h"
#include "logics/lifegame_cell.h"

class CellBase;

class Chunk : public CellOwner
{
private:
    const Field& owner_field;
    const uint64_t chunk_id;

    const sf::Vector2u chunk_size;

    std::vector<std::unique_ptr<CellBase>> cells;

public:
    ~Chunk() {}

    Chunk(const sf::Vector2u chunk_size, const uint64_t id, const Field& pf)
      : owner_field(pf)
      , chunk_id(id)
      , chunk_size(chunk_size)
    {
        const auto cell_count = get_cell_count();
        cells.reserve(cell_count);
        for (auto idx = 0; idx < cell_count; idx++)
        {
            cells.push_back(std::make_unique<LifegameCell>(*this, idx));
            cells[idx]->setState(idx % 2);
        }
    }

    virtual const CellBase& getNeighbCell(const uint64_t idx,
                                             NeighbPos pos) const override
    {
        switch (pos)
        {
            case NeighbPos::C: return *(cells[idx]);
            case NeighbPos::N:
            case NeighbPos::NE: break;
            case NeighbPos::E: return *(cells[idx + 1]);
            case NeighbPos::SE: break;
            case NeighbPos::S: break;
            case NeighbPos::SW: break;
            case NeighbPos::W: return *(cells[idx + 1]);
            case NeighbPos::NW: break;
        };
    }

    uint64_t get_cell_count() const { return chunk_size.x * chunk_size.y; }
};

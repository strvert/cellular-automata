#pragma once

#include <memory>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "game_logics/cell_owner.h"
#include "game_logics/lifegame_cell.h"

class CellBase;

class Chunk : public CellOwner
{
private:
    const Field& owner_field;

    const sf::Vector2u chunk_size;

    std::vector<std::unique_ptr<CellBase>> cells;

public:
    ~Chunk() {}

    Chunk(const sf::Vector2u chunk_size, const Field& pf)
      : owner_field(pf)
      , chunk_size(chunk_size)
    {
        const auto cell_count = getCellCount();
        cells.reserve(cell_count);
        for (auto i = 0; i < cell_count; i++)
        {
            cells.push_back(std::make_unique<LifegameCell>(*this, i));
            cells[i]->setState(i % 7 == 0);
        }
    }

    virtual CellBase& getNeighbCell(const CellOwner::CoordVector coord,
                                          NeighbPos pos) const override
    {
        auto idx = coord.y * chunk_size.x + coord.x;
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

    uint64_t getCellCount() const { return chunk_size.x * chunk_size.y; }
};

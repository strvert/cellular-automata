#pragma once

#include <SFML/System/Vector2.hpp>
#include <fmt/core.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>

#include "game_logics/chunk.h"
#include "game_logics/lifegame_cell.h"

template<typename T>
struct VectorHash {
    using result_type = std::size_t;
    result_type operator()(const sf::Vector2<T>& key) const
    {
        return std::hash<T>()(key.x) + std::hash<T>()(key.y);
    }
};

class Field
{
public:
    using ChunkCoordValueType = int64_t;
    using ChunkCoord = sf::Vector2<ChunkCoordValueType>;

private:
    std::unordered_map<ChunkCoord,
                       std::unique_ptr<Chunk>,
                       VectorHash<ChunkCoordValueType>>
      chunks;
    sf::Vector2u chunk_size = sf::Vector2u(64, 64);

public:
    Field()
    {
        chunks.insert(std::make_pair(
          ChunkCoord(0, 0), std::make_unique<Chunk>(chunk_size, 0, *this)));
    }

    sf::Vector2i getCellCount() const
    {
        return sf::Vector2i(chunk_size.x, chunk_size.y);
    }

    const CellBase& getNeighbCell(const uint64_t chunk_id,
                                  const uint64_t id,
                                  NeighbPos pos) const
    {}
    const CellBase& getCell(const ChunkCoord chunk_coord,
                            const Chunk::CoordVector cell_coord) const
    {
        // return getNeighbCell(id, NeighbPos::C);
        return chunks.at(chunk_coord)->getCell(cell_coord);
    }

    sf::Vector2u getChunkSize() const { return chunk_size; }
    void setChunkSize(const sf::Vector2u size) { chunk_size = size; }

    void update() {}
};

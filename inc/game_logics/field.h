#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
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
    sf::Vector2u chunk_size = sf::Vector2u(32, 32);

public:
    Field()
    {
        chunks.insert(std::make_pair(
          ChunkCoord(-2, -2), std::make_unique<Chunk>(chunk_size, *this)));
        chunks.insert(std::make_pair(
          ChunkCoord(0, 0), std::make_unique<Chunk>(chunk_size, *this)));
        chunks.insert(std::make_pair(
          ChunkCoord(2, 2), std::make_unique<Chunk>(chunk_size, *this)));
        chunks.insert(std::make_pair(
          ChunkCoord(10, 10), std::make_unique<Chunk>(chunk_size, *this)));
    }

    sf::Vector2i getCellCount() const
    {
        return sf::Vector2i(chunk_size.x, chunk_size.y);
    }

    CellBase* getNeighbCell(const uint64_t chunk_id,
                                  const uint64_t id,
                                  NeighbPos pos) const
    {}
    CellBase* getCell(const ChunkCoord chunk_coord,
                            const Chunk::CoordVector cell_coord) const
    {
        if (chunks.contains(chunk_coord))
        {
            return &chunks.at(chunk_coord)->getCell(cell_coord);
        }
        return nullptr;
    }

    sf::Vector2u getChunkSize() const { return chunk_size; }

    void update(const sf::Event& event) {}
};

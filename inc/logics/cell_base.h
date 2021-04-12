#pragma once

#include <cstdint>

enum class NeighbPos {
    C = 0,
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW,
};

class Field;
class CellOwner;

class CellBase
{
private:
    const CellOwner& owner;
    const uint64_t cell_id;

public:
    using CellState = uint8_t;

    CellBase(const CellOwner& own, const uint64_t id) : owner(own), cell_id(id) {}
    virtual ~CellBase() {};

    virtual uint8_t getNumOfVariations() const = 0;
    virtual CellState getState() const = 0;
    virtual void setState(CellState) = 0;

    virtual void update() = 0;
};

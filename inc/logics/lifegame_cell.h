#pragma once

#include "logics/cell_base.h"

class CellOwner;

class LifegameCell : public CellBase
{
private:
    uint8_t num_of_variations;
    CellState state;

public:
    virtual ~LifegameCell() {}

    LifegameCell(const CellOwner& own, const uint64_t id) : CellBase(own, id) {
        setState(0);
    }

    virtual uint8_t getNumOfVariations() const override
    {
        return num_of_variations;
    }

    virtual void setState(const CellState st) override { state = st; }
    virtual CellState getState() const override { return state; }
    virtual void update() override {}
};

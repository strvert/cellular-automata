#pragma once

#include "cell_base.h"

class cell_owner;

class lifegame_cell : public cell_base
{
private:
    uint8_t num_of_variations;
    cell_state state;

public:
    virtual ~lifegame_cell() {}

    lifegame_cell(const cell_owner& own, const uint64_t id) : cell_base(own, id) {
        set_state(0);
    }

    virtual uint8_t get_num_of_variations() const override
    {
        return num_of_variations;
    }

    virtual void set_state(const cell_state st) override { state = st; }
    virtual cell_state get_state() const override { return state; }
    virtual void update() override {}
};

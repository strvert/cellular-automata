#pragma once

#include <cstdint>

enum class neighb_pos {
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

class field;
class cell_owner;

class cell_base
{
private:
    const cell_owner& owner;
    const uint64_t cell_id;

public:
    using cell_state = uint8_t;

    cell_base(const cell_owner& own, const uint64_t id) : owner(own), cell_id(id) {}
    virtual ~cell_base() {};

    virtual uint8_t get_num_of_variations() const = 0;
    virtual cell_state get_state() const = 0;
    virtual void set_state(cell_state) = 0;

    virtual void update() = 0;
};

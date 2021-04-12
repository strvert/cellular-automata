#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "components/component_interface.h"

class AbstractBasicComponent : public ComponentInterface
{
private:
    int z_order = 0;
    std::string component_name;

public:
    AbstractBasicComponent(const std::string& name)
      : component_name(name)
    {}

    virtual int getZOrder() const override { return z_order; }

    virtual void setZOrder(const int z_order) override
    {
        this->z_order = z_order;
    }

    virtual const std::string& getName() const override
    {
        return component_name;
    }

    virtual void setName(const std::string& c) override { component_name = c; }
};

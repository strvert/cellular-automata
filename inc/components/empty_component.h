#pragma once

#include "components/abstract_basic_component.h"

class EmptyComponent : public AbstractBasicComponent
{
private:
    sf::Vector2f position;

public:
    EmptyComponent(const std::string& name, const sf::Vector2f& pos = sf::Vector2f(0, 0))
      : AbstractBasicComponent(name)
      , position(pos)
    {}

    /* Drawable override methods */
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override
    {}

    /* component_interface methods */
    virtual sf::FloatRect getGlobalBounds() const override
    {
        return sf::FloatRect(position.x, position.y, 0, 0);
    }
    virtual sf::FloatRect getLocalBounds() const override
    {
        return sf::FloatRect();
    }
};

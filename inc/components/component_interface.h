#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

class ComponentInterface : public sf::Drawable
{
public:
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual sf::FloatRect getLocalBounds() const = 0;

    virtual int getZOrder() const = 0;
    virtual void setZOrder(const int z_order) = 0;

    virtual const std::string& getName() const = 0;
    virtual void setName(const std::string& c) = 0;
};

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

class ComponentInterface : public sf::Drawable
{
    virtual sf::IntRect getGlobalBounds() const = 0;
    virtual sf::IntRect getLocalBounds() const = 0;
};

#pragma once

#include <concepts>
#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

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

template<typename T>
concept Component = std::derived_from<T, ComponentInterface>;

template<typename To>
bool checkComponentConvertibility(
  const std::unique_ptr<ComponentInterface>& ptr)
{
    return dynamic_cast<To*>(ptr.get());
}

template<Component To>
To& componentCastedRef(const std::unique_ptr<ComponentInterface>& ptr)
{
    return *dynamic_cast<To*>(ptr.get());
}

#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <fmt/core.h>

#include "components/component_interface.h"
#include "components/empty_component.h"

class EventHandler
{
};

using ComponentPtr = std::unique_ptr<ComponentInterface>;
using ComponentMap = std::map<uint64_t, ComponentPtr>;

class ComponentContainer : public sf::Drawable
{
private:
    ComponentMap components;

public:
    void insert(ComponentMap::value_type&& e);
    ComponentMap::iterator begin() { return components.begin(); }
    ComponentMap::iterator end() { return components.end(); }

    ComponentMap::mapped_type& operator[](const ComponentMap::key_type& x);

    /* Drawable methods */
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override
    {
        for (auto&& [id, c] : components) { target.draw(*c, states); }
    }
};

class ComponentManager
{
public:
    ComponentContainer components;
    bool mouse_left_clicked = false;

private:
    uint64_t head_id = 0;

    const ComponentPtr null_component =
      std::unique_ptr<EmptyComponent>(nullptr); // for error

public:
    ComponentManager() {}

    uint64_t addComponent(ComponentPtr&& component);

    const std::unique_ptr<ComponentInterface>& getComponentByName(
      const std::string& name);

    const std::unique_ptr<ComponentInterface>& getComponentById(
      const uint64_t id);

    void eventProc(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                fmt::print("mouse button pressed [x: {}, y: {}]\n",
                           event.mouseButton.x,
                           event.mouseButton.y);
                mouse_left_clicked = true;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                fmt::print("mouse button pressed [x: {}, y: {}]\n",
                           event.mouseButton.x,
                           event.mouseButton.y);
                mouse_left_clicked = false;
            }
        }
        if (event.type == sf::Event::MouseMoved)
        {
            if (mouse_left_clicked)
            {
                // auto x = event.mouseMove.x;
                // auto y = event.mouseMove.y;
                // field_sprite.setPosition(x, y);
            }
        }
    }

    void update();
};

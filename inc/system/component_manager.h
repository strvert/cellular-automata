#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <optional>

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

private:
    uint64_t head_id = 0;

    const ComponentPtr null_component =
      std::unique_ptr<EmptyComponent>(nullptr); // for error

    uint64_t current_active_component;

public:
    ComponentManager() {}

    uint64_t addComponent(ComponentPtr&& component);

    const std::unique_ptr<ComponentInterface>& getComponentByName(
      const std::string& name);

    const std::unique_ptr<ComponentInterface>& getComponentById(
      const uint64_t id);

    uint64_t getActiveComponent(const uint64_t id) const;
    void setActiveComponent(const uint64_t id);

    void eventProc(const sf::Event& event);
    void update();
};

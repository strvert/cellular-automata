#pragma once

#include <algorithm>
#include <map>
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
    void insert(ComponentMap::value_type&& e)
    {
        components.insert(std::move(e));
    }
    ComponentMap::iterator begin() { return components.begin(); }
    ComponentMap::iterator end() { return components.end(); }

    ComponentMap::mapped_type& operator[](const ComponentMap::key_type& x)
    {
        return components[x];
    }

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

public:
    ComponentManager() {}

    uint64_t addComponent(ComponentPtr&& component)
    {
        auto id = head_id++;
        components.insert(std::make_pair(id, std::move(component)));
        return id;
    }

    const std::unique_ptr<ComponentInterface>& getComponentByName(
      const std::string& name)
    {
        auto k = std::find_if(
          components.begin(), components.end(), [&](const auto& e) {
              return e.second->getName() == name;
          });
        if (k->second) { return k->second; }
        else
        {
            return null_component;
        }
    }

    const std::unique_ptr<ComponentInterface>& getComponentById(
      const uint64_t id)
    {
        return components[id];
    }

    void recvEvent(const sf::Event& event) {}
    void update()
    {
        // fmt::print("update\n");
        // for (auto&& [id, c] : components)
        // {
        //     fmt::print("{}({}): {}\n", c->getName(), id, c->getZOrder());
        // }
        // fmt::print("\n");
    }
};

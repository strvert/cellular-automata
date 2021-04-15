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

class ComponentDrawableReferencer : public sf::Drawable
{
private:
    const ComponentMap& components_ref;

public:
    ComponentDrawableReferencer(const ComponentMap& cr)
      : components_ref(cr)
    {}

    /* Drawable methods */
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override
    {
        for (auto&& [id, c] : components_ref) { target.draw(*c, states); }
    }
};

class ComponentManager
{
private:
    uint64_t head_id = 0;
    const ComponentPtr null_component =
      std::unique_ptr<EmptyComponent>(nullptr); // for error

    uint64_t current_active_component = 0;

    uint64_t left_click_start_component;

public:
    ComponentMap components;
    ComponentDrawableReferencer drawable_refs;


public:
    ComponentManager()
      : drawable_refs(components)
    {
        setActiveComponent(0);
    }

    uint64_t addComponent(ComponentPtr&& component);

    ComponentInterface& getComponentByName(const std::string& name) const;

    ComponentInterface& getComponentById(const uint64_t id) const;
    std::pair<uint64_t, ComponentInterface&> getComponentByPosition(
      const sf::Vector2f pos) const;
    std::pair<uint64_t, ComponentInterface&> getActiveComponent() const;
    void setActiveComponent(const uint64_t id);
    const ComponentDrawableReferencer& getDrawableObject() const;

    void update(const sf::Event& event);

    void next_step();
};

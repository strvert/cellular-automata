#include "system/component_manager.h"

uint64_t ComponentManager::addComponent(ComponentPtr&& component)
{
    const auto id = head_id++;
    components.insert(std::make_pair(id, std::move(component)));
    return id;
}

ComponentInterface& ComponentManager::getComponentByName(
  const std::string& name) const
{
    const auto k =
      std::find_if(components.cbegin(), components.cend(), [&](const auto& e) {
          return e.second->getName() == name;
      });
    if (k->second) { return *k->second; }
    else
    {
        return *null_component;
    }
}

ComponentInterface& ComponentManager::getComponentById(const uint64_t id) const
{
    return *components.at(id);
}

void ComponentManager::setActiveComponent(const uint64_t id)
{
    current_active_component = id;
}

std::pair<uint64_t, ComponentInterface&>
ComponentManager::getComponentByPosition(const sf::Vector2f pos) const
{
    for (auto &&iter = components.rbegin(), e = components.rend(); iter != e;
         ++iter)
    {
        if (iter->second->getGlobalBounds().contains(pos))
        {
            return { iter->first, *iter->second };
        }
    }
    return { 0, *null_component };
}

std::pair<uint64_t, ComponentInterface&> ComponentManager::getActiveComponent()
  const
{
    return { current_active_component,
             *components.at(current_active_component) };
}

const ComponentDrawableReferencer& ComponentManager::getDrawableObject() const
{
    return drawable_refs;
}

void ComponentManager::eventProc(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            auto [id, cmp] = getComponentByPosition(
              sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            setActiveComponent(id);
        }
    }
    auto [id, cmp] = getActiveComponent();
    cmp.eventProc(event);
}

void ComponentManager::update(const double delta) {}
void ComponentManager::next_step() {}

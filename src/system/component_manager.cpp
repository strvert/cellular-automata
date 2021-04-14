#include "system/component_manager.h"

void ComponentContainer::insert(ComponentMap::value_type&& e)
{
    components.insert(std::move(e));
}

ComponentMap::mapped_type& ComponentContainer::operator[](
  const ComponentMap::key_type& x)
{
    return components[x];
}

uint64_t ComponentManager::addComponent(ComponentPtr&& component)
{
    const auto id = head_id++;
    components.insert(std::make_pair(id, std::move(component)));
    return id;
}

const std::unique_ptr<ComponentInterface>& ComponentManager::getComponentByName(
  const std::string& name)
{
    const auto k =
      std::find_if(components.begin(), components.end(), [&](const auto& e) {
          return e.second->getName() == name;
      });
    if (k->second) { return k->second; }
    else
    {
        return null_component;
    }
}

const std::unique_ptr<ComponentInterface>& ComponentManager::getComponentById(
  const uint64_t id)
{
    return components[id];
}

void ComponentManager::update()
{
    // fmt::print("update\n");
    // for (auto&& [id, c] : components)
    // {
    //     fmt::print("{}({}): {}\n", c->getName(), id, c->getZOrder());
    // }
    // fmt::print("\n");
}

void ComponentManager::setActiveComponent(const uint64_t id)
{
    current_active_component = id;
}

uint64_t ComponentManager::getActiveComponent(const uint64_t id) const
{
    return current_active_component;
}

void ComponentManager::eventProc(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
        }
    }
    for (auto&& [k, c] : components) { c->eventProc(event); }
}

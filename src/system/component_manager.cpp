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
    auto id = head_id++;
    components.insert(std::make_pair(id, std::move(component)));
    return id;
}

const std::unique_ptr<ComponentInterface>& ComponentManager::getComponentByName(
  const std::string& name)
{
    auto k =
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

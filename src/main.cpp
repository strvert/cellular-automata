#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fmt/core.h>

#include "components/cellular_automata_component.h"
#include "components/empty_component.h"

#include "system/component_manager.h"

constexpr const uint32_t WINDOW_WIDTH = 1920;
constexpr const uint32_t WINDOW_HEIGHT = 1080;

template<typename T>
auto componentCastWithExit =
  [](const std::unique_ptr<ComponentInterface>& c) -> T& {
    if (checkComponentConvertibility<T>(c)) { return componentCastedRef<T>(c); }
    else
    {
        fmt::print("Failed to cast the component.\n");
        std::exit(1);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "lifegame");
    sf::Event event;

    bool mouse_left_clicked = false;

    ComponentManager manager;

    auto id_1 = manager.addComponent([] {
        auto e = std::make_unique<CellularAutomataComponent>(
          "game_c", sf::Vector2f(10, 10), sf::Vector2f(1070, 1070));
        e->renderer.setCellSize(9);
        e->renderer.setThickLinePt(5);
        e->renderer.setCellColor(sf::Color::Red);
        return e;
    }());

    auto& cac = componentCastWithExit<CellularAutomataComponent>(
      manager.getComponentById(id_1));
    cac.renderer.setCellColor(sf::Color::Blue);

    float pos = 0;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    break;
                }
            }
            manager.eventProc(event);
        }

        window.clear(sf::Color::Black);

        manager.update();

        cac.renderer.setLookingPosition(sf::Vector2f(pos, pos));
        pos += 3;

        window.draw(manager.components);

        window.display();
    }
}

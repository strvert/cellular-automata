#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include <chrono>
#include <cstdint>
#include <optional>
#include <vector>

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

    ComponentManager manager;

    auto id_1 = manager.addComponent([] {
        auto e = std::make_unique<CellularAutomataComponent>(
          "game_c", sf::Vector2f(10, 10), sf::Vector2f(1000, 1000));
        e->renderer.setCellSize(10);
        e->renderer.setThickLinePt(2);
        e->renderer.setCellColor(sf::Color::Blue);
        return e;
    }());

    // auto id_2 = manager.addComponent([] {
    //     auto e = std::make_unique<CellularAutomataComponent>(
    //       "game_c", sf::Vector2f(600, 10), sf::Vector2f(500, 500));
    //     e->renderer.setCellSize(10);
    //     e->renderer.setThickLinePt(2);
    //     e->renderer.setCellColor(sf::Color::Red);
    //     return e;
    // }());

    auto& cac_1 = componentCastWithExit<CellularAutomataComponent>(
      manager.getComponentById(id_1));

    // auto& cac_2 = componentCastWithExit<CellularAutomataComponent>(
    //   manager.getComponentById(id_2));

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    float pos = 0;
    while (window.isOpen())
    {
        double delta_time = std::chrono::duration<double>(end - start).count();
        start = std::chrono::system_clock::now();
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

        // pos -= 100 * delta_time;
        // cac_1.renderer.setLookingPosition(sf::Vector2f(200+pos, 200+pos));

        window.draw(manager.components);

        window.display();
        end = std::chrono::system_clock::now();
    }
}

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fmt/core.h>

#include "components/cellular_automata_component.h"
#include "components/empty_component.h"

#include "system/component_manager.h"

constexpr const uint32_t WINDOW_WIDTH = 1920;
constexpr const uint32_t WINDOW_HEIGHT = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "lifegame");
    sf::Event event;

    bool mouse_left_clicked = false;

    ComponentManager manager;

    auto id_1 = manager.addComponent([] {
        auto e = std::make_unique<CellularAutomataComponent>(
          "game_c", sf::Vector2f(10, 10), sf::Vector2f(1080, 1080));
        e->renderer.setCellSize(25);
        e->renderer.setThickLinePt(5);
        e->renderer.setCellColor(sf::Color::Red);
        return e;
    }());

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

        window.draw(manager.components);

        window.display();
    }
}

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

    auto id_1 = manager.addComponent([]() {
        auto e = std::make_unique<CellularAutomataComponent>(
          "game_c",
          sf::Vector2f(10, 10),
          sf::Vector2f(60, 60),
          sf::Vector2f(100, 100));
        e->setZOrder(-1);
        return e;
    }());
    auto id_2 = manager.addComponent([]() {
        auto e = std::make_unique<CellularAutomataComponent>(
          "game_c",
          sf::Vector2f(500, 15),
          sf::Vector2f(60, 60),
          sf::Vector2f(100, 100));
        e->renderer.setGridColor(sf::Color::Cyan);
        e->setZOrder(1);
        return e;
    }());

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
            manager.recvEvent(event);

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

        window.clear(sf::Color::Black);

        manager.update();
        window.draw(manager.components);

        window.display();
    }
}

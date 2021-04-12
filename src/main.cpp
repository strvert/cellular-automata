#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fmt/core.h>

#include "components/cellular_automata_component.h"

constexpr const uint32_t WINDOW_WIDTH = 1920;
constexpr const uint32_t WINDOW_HEIGHT = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "lifegame");
    sf::Event event;

    bool mouse_left_clicked = false;

    sf::Sprite cac1_sprite;
    CellularAutomataComponent cac1(cac1_sprite, sf::Vector2f(10, 10), sf::Vector2f(60, 60), sf::Vector2f(100, 100));

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }

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

        cac1.render();

        window.draw(cac1);
        {
            auto rect = cac1.getLocalBounds();
            fmt::print("{}, {}, {}, {}\n", rect.left, rect.top, rect.width, rect.height);
        }
        {
            auto rect = cac1.getGlobalBounds();
            fmt::print("{}, {}, {}, {}\n", rect.left, rect.top, rect.width, rect.height);
        }

        window.display();
    }
}

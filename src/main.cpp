#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fmt/core.h>

#include "field.h"
#include "field_renderer.h"

constexpr const uint32_t WINDOW_WIDTH = 1920;
constexpr const uint32_t WINDOW_HEIGHT = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "lifegame");
    sf::Event event;

    bool mouse_left_clicked = false;

    sf::RenderTexture field_texture;
    sf::Sprite field_sprite;

    field fie(70, 90);
    field_renderer fr(fie, field_texture);

    fr.set_cell_size(12);
    fr.set_grid_color(sf::Color(255, 255, 255));
    field_sprite.setTexture(field_texture.getTexture());
    field_sprite.setPosition(10, 10);

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
                    auto x = event.mouseMove.x;
                    auto y = event.mouseMove.y;
                    field_sprite.setPosition(x, y);
                }
            }
        }

        window.clear(sf::Color::Black);

        fr.render();

        window.draw(field_sprite);
        window.display();
    }
}

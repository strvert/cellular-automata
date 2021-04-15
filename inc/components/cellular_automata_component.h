#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "components/abstract_basic_component.h"
#include "game_logics/field.h"
#include "renderers/field_renderer.h"
#include "system/utils.h"

class CellularAutomataComponent : public AbstractBasicComponent
{
private:
    sf::RenderTexture field_texture;
    sf::Sprite field_sprite;

private:
    sf::Vector2i mouse_left_pressed_point;
    sf::Vector2i mouse_left_released_point;
    sf::Vector2f drag_before_point;
    bool mouse_left_pressing = false;

public:
    Field ca_field;
    FieldRenderer renderer;

    CellularAutomataComponent()
      : CellularAutomataComponent("cellular_automata_component_default",
                                  sf::Vector2f(0, 0),
                                  sf::Vector2f(100, 100))

    {}

    CellularAutomataComponent(const std::string& name,
                              const sf::Vector2f frame_pos,
                              const sf::Vector2f frame_size)
      : AbstractBasicComponent(name)
      , renderer(ca_field, field_texture, frame_size)
    {
        field_sprite.setTexture(field_texture.getTexture());
        field_sprite.setPosition(frame_pos);
    }

    void render() const { renderer.render(); }

    const sf::Sprite& getSprite() { return field_sprite; }

    /* Drawable methods */
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override
    {
        render();
        target.draw(field_sprite, states);
    }

    /* component_interface methods */
    virtual sf::FloatRect getGlobalBounds() const override
    {
        return field_sprite.getGlobalBounds();
    }
    virtual sf::FloatRect getLocalBounds() const override
    {
        return field_sprite.getLocalBounds();
    }
    virtual void eventProc(const sf::Event& event) override
    {
        switch (event.type)
        {
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    drag_before_point = renderer.getLookingPosition();
                    mouse_left_pressed_point =
                      sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                    mouse_left_pressing = true;
                }
                return;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouse_left_released_point =
                      sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                    mouse_left_pressing = false;
                }
                return;
            case sf::Event::MouseMoved:
                if (mouse_left_pressing &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    auto pos =
                      sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                    renderer.setLookingPosition(utils::convertVector<float>(
                      utils::convertVector<int>(drag_before_point) +
                      mouse_left_pressed_point - pos));
                }
                return;
            default: break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            const auto b_cs = renderer.getCellSize();
            const auto a_cs = b_cs + 0.1;
            const auto rat = a_cs / b_cs;
            if (renderer.setCellSize(a_cs))
            {
                auto lp = renderer.getLookingPosition();
                renderer.setLookingPosition(
                  sf::Vector2f(lp.x * rat, lp.y * rat));
            }
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            const auto b_cs = renderer.getCellSize();
            const auto a_cs = b_cs - 0.1;
            const auto rat = a_cs / b_cs;
            if (renderer.setCellSize(a_cs))
            {
                auto lp = renderer.getLookingPosition();
                renderer.setLookingPosition(
                  sf::Vector2f(lp.x * rat, lp.y * rat));
            }
            return;
        }

        ca_field.eventProc(event);
    }
    virtual void update(const double delta) override {}
};

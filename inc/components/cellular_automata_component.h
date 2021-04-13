#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "components/abstract_basic_component.h"
#include "game_logics/field.h"
#include "renderers/field_renderer.h"

class CellularAutomataComponent : public AbstractBasicComponent
{
private:
    sf::RenderTexture field_texture;
    sf::Sprite field_sprite;

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
};

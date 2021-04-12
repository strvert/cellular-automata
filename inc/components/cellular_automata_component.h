#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "components/component_interface.h"
#include "logics/field.h"
#include "renderers/field_renderer.h"

class CellularAutomataComponent
  : public ComponentInterface
{
private:
    sf::RenderTexture field_texture;
    sf::Sprite& field_sprite;

public:
    Field ca_field;
    FieldRenderer renderer;

    CellularAutomataComponent(sf::Sprite& fs,
                                const sf::Vector2f frame_pos,
                                const sf::Vector2f frame_size,
                                const sf::Vector2f field_size)
      : field_sprite(fs)
      , ca_field(field_size)
      , renderer(ca_field, field_texture, frame_size)
    {
        field_sprite.setTexture(field_texture.getTexture());
        field_sprite.setPosition(frame_pos);
    }

    void render() const { renderer.render(); }

    const sf::Sprite& getSprite() { return field_sprite; }


    /* Drawable methods */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        render();
        target.draw(field_sprite, states);
    }


    /* component_interface methods */
    virtual sf::FloatRect getGlobalBounds() const override {
        return field_sprite.getGlobalBounds();
    }
    virtual sf::FloatRect getLocalBounds() const override {
        return field_sprite.getLocalBounds();
    }
};

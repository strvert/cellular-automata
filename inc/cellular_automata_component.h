#pragma once
#include <SFML/Graphics.hpp>

#include "field.h"
#include "field_renderer.h"

class cellular_automata_component
  : public sf::Drawable
  , public sf::Transformable
{
private:
    sf::RenderTexture field_texture;
    sf::Sprite& field_sprite;

public:
    field ca_field;
    field_renderer renderer;

    cellular_automata_component(sf::Sprite& fs,
                                const sf::Vector2u frame_pos,
                                const sf::Vector2u frame_size,
                                const sf::Vector2u field_size)
      : field_sprite(fs)
      , ca_field(field_size)
      , renderer(ca_field, field_texture, frame_size)
    {
        field_sprite.setTexture(field_texture.getTexture());
        field_sprite.setPosition(frame_pos.x, frame_pos.y);
    }

    void render() const { renderer.render(); }

    const sf::Sprite& get_sprite() { return field_sprite; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        render();
        target.draw(field_sprite, states);
    }
};

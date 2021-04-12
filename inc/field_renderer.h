#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fmt/core.h>

#include "field.h"

class field_renderer
{
private:
    sf::Color cell_color;
    uint32_t cell_size;

    sf::Color bg_color;
    sf::Color grid_color;
    bool grid_visibility;

    uint16_t thick_line_pt;
    uint16_t thin_line_pt;

    const field& target_field;
    sf::RenderTexture& texture;

    sf::Vector2u frame_size;

public:
    field_renderer(const field& f,
                   sf::RenderTexture& tex,
                   const sf::Vector2u frame_size)
      : target_field(f)
      , texture(tex)
      , frame_size(frame_size)
    {
        set_cell_color(sf::Color(0, 255, 0, 255));
        set_bg_color(sf::Color(10, 10, 10, 255));
        set_grid_color(sf::Color(20, 20, 20, 255));
        set_cell_size(10);
        set_grid_visible(true);
        set_thick_line_pt(2);
        set_thin_line_pt(1);

        auto s = get_field_pixel_size();
        texture.create(s.x + thick_line_pt / 2, s.y + thick_line_pt / 2);
        texture.setSmooth(true);
    }

    sf::Vector2u get_field_pixel_size() const;

    void set_cell_color(const sf::Color col) { cell_color = col; }
    void set_bg_color(const sf::Color col) { bg_color = col; }
    void set_grid_color(const sf::Color col) { grid_color = col; }
    void set_cell_size(const uint32_t size) { cell_size = size; }
    void set_grid_visible(bool b) { grid_visibility = b; }
    void set_thick_line_pt(const uint16_t pt) { thick_line_pt = pt; }
    void set_thin_line_pt(const uint16_t pt) { thin_line_pt = pt; }

    void draw_grid() const;
    void draw_frame() const;
    void draw_cells() const;
    void render() const;
};

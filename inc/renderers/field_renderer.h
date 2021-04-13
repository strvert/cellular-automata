#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fmt/core.h>

#include "game_logics/field.h"

class FieldRenderer
{
private:
    sf::Color cell_color;
    uint32_t cell_size;

    sf::Color bg_color;
    sf::Color grid_color;
    bool grid_visibility;

    float thick_line_pt;
    float thin_line_pt;
    uint16_t thick_line_interval;

    const Field& target_field;
    sf::RenderTexture& texture;

    sf::Vector2i frame_size;
    sf::Vector2f looking_pos;

public:
    FieldRenderer(const Field& f,
                   sf::RenderTexture& tex,
                   const sf::Vector2f frame_size)
      : target_field(f)
      , texture(tex)
      , frame_size(frame_size)
    {
        setCellColor(sf::Color(0, 255, 0, 255));
        setBgColor(sf::Color(10, 10, 10, 255));
        setGridColor(sf::Color(30, 30, 30, 255));
        setCellSize(10);
        setGridVisible(true);
        setThickLinePt(2);
        setThinLinePt(1);
        setThickLineInterval(10);
        setLookingPosition(sf::Vector2f(0, 0));

        texture.create(frame_size.x, frame_size.y);
        texture.setSmooth(true);
    }

    void setCellColor(const sf::Color col) { cell_color = col; }
    void setBgColor(const sf::Color col) { bg_color = col; }
    void setGridColor(const sf::Color col) { grid_color = col; }
    void setCellSize(const uint32_t size) { cell_size = size; }
    void setGridVisible(bool b) { grid_visibility = b; }
    void setThickLinePt(const uint16_t pt) { thick_line_pt = pt; }
    void setThinLinePt(const uint16_t pt) { thin_line_pt = pt; }
    void setThickLineInterval(const uint16_t interval) { thick_line_interval = interval; }
    void setLookingPosition(const sf::Vector2f pos) { looking_pos = pos; }

    std::vector<Field::ChunkCoord> calcLookingChunks() const;

    void drawBackground() const;
    void drawGrid() const;
    void drawFrame() const;
    void drawCells() const;
    void render() const;
};

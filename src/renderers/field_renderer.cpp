#include "renderers/field_renderer.h"
#include <cmath>

std::vector<Field::ChunkCoord> FieldRenderer::calcLookingChunks() const
{
    auto size = target_field.getChunkSize();
    auto left_top_chunk_coord =
      sf::Vector2<int64_t>(std::floor(looking_pos.x / (size.x * cell_size)),
                           std::floor(looking_pos.y / (size.y * cell_size)));
    auto right_bottom_chunk_coord = sf::Vector2<int64_t>(
      std::floor((looking_pos.x + frame_size.x) / (size.x * cell_size)),
      std::floor((looking_pos.y + frame_size.y) / (size.y * cell_size)));

    std::vector<Field::ChunkCoord> res;
    for (auto x = left_top_chunk_coord.x; x <= right_bottom_chunk_coord.x; x++)
    {
        for (auto y = left_top_chunk_coord.y; y <= right_bottom_chunk_coord.y;
             y++)
        {
            res.push_back(Field::ChunkCoord(x, y));
        }
    }

    return res;
}

void FieldRenderer::drawBackground() const
{
    auto background =
      sf::RectangleShape(sf::Vector2f(frame_size.x, frame_size.y));
    background.setFillColor(bg_color);
    texture.draw(background);
}

void FieldRenderer::drawGrid() const
{
    auto offset = sf::Vector2f(std::fmod(looking_pos.x, cell_size),
                               std::fmod(looking_pos.y, cell_size));
    auto curr_thick_line = sf::Vector2u(
      std::abs(std::fmod(looking_pos.x, cell_size * thick_line_interval) /
               cell_size),
      std::abs(std::fmod(looking_pos.y, cell_size * thick_line_interval) /
               cell_size));

    auto in_plus = sf::Vector2<bool>(looking_pos.x >= 0, looking_pos.y >= 0);

    for (auto w = 0; w * cell_size <= frame_size.x + cell_size; w++)
    {
        auto [v_line, line_pt] = [&] {
            if (w % thick_line_interval == in_plus.x * (thick_line_interval-1) - curr_thick_line.x)
            {
                return std::make_pair(
                  sf::RectangleShape(sf::Vector2f(thick_line_pt, frame_size.y)),
                  thick_line_pt);
            }
            else
            {
                return std::make_pair(
                  sf::RectangleShape(sf::Vector2f(thin_line_pt, frame_size.y)),
                  thin_line_pt);
            }
        }();
        v_line.setFillColor(grid_color);
        v_line.setPosition(w * cell_size - offset.x - (line_pt / 2), 0);
        texture.draw(v_line);
    }
    for (auto h = 0; h * cell_size <= frame_size.y + cell_size; h++)
    {
        auto [h_line, line_pt] = [&] {
            if (h % thick_line_interval == in_plus.y * (thick_line_interval-1) - curr_thick_line.y)
            {
                return std::make_pair(
                  sf::RectangleShape(sf::Vector2f(frame_size.x, thick_line_pt)),
                  thick_line_pt);
            }
            else
            {
                return std::make_pair(
                  sf::RectangleShape(sf::Vector2f(frame_size.x, thin_line_pt)),
                  thin_line_pt);
            }
        }();
        h_line.setFillColor(grid_color);
        h_line.setPosition(0, h * cell_size - offset.y - (line_pt / 2));
        texture.draw(h_line);
    }
}

void FieldRenderer::drawFrame() const
{
    auto left =
      sf::RectangleShape(sf::Vector2f(thick_line_pt + 2, frame_size.y));
    left.setFillColor(grid_color);
    texture.draw(left);

    auto top =
      sf::RectangleShape(sf::Vector2f(frame_size.x, thick_line_pt + 2));
    top.setFillColor(grid_color);
    texture.draw(top);
}

void FieldRenderer::drawCells() const
{
    const auto& field_cnt = target_field.getCellCount();
    auto cell_shape = sf::RectangleShape(sf::Vector2f(cell_size, cell_size));

    for (auto y = 0; y < field_cnt.y; y++)
    {
        for (auto x = 0; x < field_cnt.x; x++)
        {
            auto& state = target_field.getCell(Field::ChunkCoord(0, 0),
                                               CellOwner::CoordVector(x, y));

            // FIXME: 局所的なルールにしか対応していない
            if (state.getState() == 1)
            {
                cell_shape.setFillColor(cell_color);
                cell_shape.setPosition(x * cell_size - looking_pos.x,
                                       y * cell_size - looking_pos.y);
                texture.draw(cell_shape);
            }
        }
    }
}

void FieldRenderer::render() const
{
    drawBackground();
    if (grid_visibility) { drawGrid(); }
    drawFrame();

    auto&& chunks = calcLookingChunks();

    drawCells();
    texture.display();
}

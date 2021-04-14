#include "renderers/field_renderer.h"
#include "system/utils.h"
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
      sf::RectangleShape(utils::convertVector<float>(frame_size));
    background.setFillColor(bg_color);
    texture.draw(background);
}

void FieldRenderer::drawGrid() const
{
    auto offset = sf::Vector2f(std::fmod(looking_pos.x, cell_size),
                               std::fmod(looking_pos.y, cell_size));
    auto curr_thick_line = sf::Vector2f(
      (std::fmod(looking_pos.x, cell_size * thick_line_interval) / cell_size),
      (std::fmod(looking_pos.y, cell_size * thick_line_interval) / cell_size));
    auto calcThickLinePos = [&](float lp, float p) {
        if (lp <= 0) { return static_cast<int>(std::abs(std::ceil(p))); }
        else if (lp > 0)
        {
            return static_cast<int>(thick_line_interval - std::floor(p));
        }
        else
        {
            return 0;
        }
    };

    for (auto w = 0; w * cell_size <= frame_size.x + cell_size; w++)
    {
        auto [v_line, line_pt] = [&] {
            if (w % thick_line_interval ==
                calcThickLinePos(looking_pos.x, curr_thick_line.x))
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
            if (h % thick_line_interval ==
                calcThickLinePos(looking_pos.y, curr_thick_line.y))
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
    sf::RectangleShape left(sf::Vector2f(thick_line_pt + 2, frame_size.y));
    left.setFillColor(grid_color);
    texture.draw(left);

    sf::RectangleShape top(sf::Vector2f(frame_size.x, thick_line_pt + 2));
    top.setFillColor(grid_color);
    texture.draw(top);
}

void FieldRenderer::drawCells(
  const std::vector<Field::ChunkCoord>& looking) const
{
    const auto& chunk_size = target_field.getChunkSize();
    const auto chunk_px_x = cell_size * chunk_size.x;
    const auto chunk_px_y = cell_size * chunk_size.y;
    auto cell_shape = sf::RectangleShape(sf::Vector2f(cell_size, cell_size));
    const auto& start = looking[0];

    for (auto&& c : looking)
    {
        for (auto y = 0; y < chunk_size.y; y++)
        {
            for (auto x = 0; x < chunk_size.x; x++)
            {
                const CellBase* cell;
                if (cell =
                      target_field.getCell(c, CellOwner::CoordVector(x, y));
                    !cell)
                {
                    continue;
                }

                // FIXME: 局所的なルールにしか対応していない
                if (cell->getState() == 1)
                {
                    cell_shape.setFillColor(cell_color);
                    cell_shape.setPosition(
                      (c.x - start.x) * chunk_px_x + x * cell_size -
                        (looking_pos.x < 0 ? 1 : 0) * chunk_px_x - std::fmod(looking_pos.x, chunk_px_x),
                      (c.y - start.y) * chunk_px_y + y * cell_size -
                        (looking_pos.y < 0 ? 1 : 0) * chunk_px_y - std::fmod(looking_pos.y, chunk_px_y));
                    texture.draw(cell_shape);
                }
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
    // for (auto&& c : chunks) { fmt::print("{}, {}\n", c.x, c.y); }
    // fmt::print("\n");

    drawCells(chunks);
    texture.display();
}

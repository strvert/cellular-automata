#include "renderers/field_renderer.h"

sf::Vector2u FieldRenderer::getFieldPixelSize() const
{
    const auto& cnt = target_field.getCellCount();
    return sf::Vector2u(cell_size * cnt.x, cell_size * cnt.y);
}

void FieldRenderer::drawGrid() const
{
    const auto& field_cnt = target_field.getCellCount();
    auto size = texture.getSize();

    for (auto w = 1; w < field_cnt.x; w++)
    {
        auto v_line = [&] {
            if (w % 10 == 0)
            {
                return sf::RectangleShape(
                  sf::Vector2f(thick_line_pt, size.y));
            }
            else
            {
                return sf::RectangleShape(
                  sf::Vector2f(thin_line_pt, size.y));
            }
        }();
        v_line.setFillColor(grid_color);
        v_line.setPosition(w * cell_size, 0);
        texture.draw(v_line);
    }
    for (auto h = 1; h < field_cnt.y; h++)
    {
        auto h_line = [&] {
            if (h % 10 == 0)
            {
                return sf::RectangleShape(
                  sf::Vector2f(size.x, thick_line_pt));
            }
            else
            {
                return sf::RectangleShape(
                  sf::Vector2f(size.x, thin_line_pt));
            }
        }();
        h_line.setFillColor(grid_color);
        h_line.setPosition(0, h * cell_size);
        texture.draw(h_line);
    }
}

void FieldRenderer::drawFrame() const
{
    const auto s = texture.getSize();

    auto left = sf::RectangleShape(sf::Vector2f(thick_line_pt, s.y));
    left.setFillColor(grid_color);
    texture.draw(left);

    auto right = sf::RectangleShape(sf::Vector2f(thick_line_pt, s.y));
    right.setPosition(s.x - thick_line_pt / 2.f, 0);
    right.setFillColor(grid_color);
    texture.draw(right);

    auto top = sf::RectangleShape(sf::Vector2f(s.x, thick_line_pt));
    top.setFillColor(grid_color);
    texture.draw(top);

    auto bottom = sf::RectangleShape(sf::Vector2f(s.x, thick_line_pt));
    bottom.setPosition(0, s.y - thick_line_pt / 2.f);
    bottom.setFillColor(grid_color);
    texture.draw(bottom);
}

void FieldRenderer::drawCells() const
{
}

void FieldRenderer::render() const
{
    if (grid_visibility) { drawGrid(); }
    drawFrame();
    texture.display();
}

#include "field_renderer.h"

sf::Vector2u field_renderer::get_field_pixel_size() const
{
    const auto& w = target_field.get_x_cell_count();
    const auto& h = target_field.get_y_cell_count();
    return sf::Vector2u(cell_size * w, cell_size * h);
}

void field_renderer::draw_grid() const
{
    const auto& field_w = target_field.get_x_cell_count();
    const auto& field_h = target_field.get_y_cell_count();
    auto size = texture.getSize();

    for (auto w = 1; w < field_w; w++)
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
    for (auto h = 1; h < field_h; h++)
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

void field_renderer::draw_frame() const
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

void field_renderer::draw_cells() const
{
}

void field_renderer::render() const
{
    if (grid_visibility) { draw_grid(); }
    draw_frame();
    texture.display();
}

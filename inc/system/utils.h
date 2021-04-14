#pragma once

#include <SFML/System/Vector2.hpp>

class utils
{
public:
    template<typename T, typename U>
    static sf::Vector2<T> convertVector(const sf::Vector2<U>& v)
    {
        return sf::Vector2<T>(v.x, v.y);
    }
};

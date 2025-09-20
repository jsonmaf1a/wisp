#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace PositionUtils
{
    template <typename T>
        requires std::is_arithmetic_v<T>
    static inline sf::Vector2f normalizePosition(const sf::Vector2<T> &pos,
                                                 const sf::RenderWindow &window)
    {
        return {static_cast<float>(pos.x) / window.getSize().x,
                static_cast<float>(pos.y) / window.getSize().y};
    }
} // namespace PositionUtils

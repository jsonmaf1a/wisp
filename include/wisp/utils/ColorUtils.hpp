#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ColorUtils
{
    static sf::Color dim(sf::Color color, float factor = 0.95f)
    {
        return sf::Color(color.r * factor, color.g * factor, color.b * factor,
                         color.a);
    }

    static sf::Color blend(sf::Color color, sf::Color blendColor,
                           float factor = 0.95f, float alpha = 0.f)
    {
        if(alpha == 0.f)
            alpha = color.a;

        return sf::Color(color.r + (blendColor.r - color.r) * factor,
                         color.g + (blendColor.g - color.g) * factor,
                         color.b + (blendColor.b - color.b) * factor,
                         color.a + (blendColor.a - color.a) * alpha);
    }
} // namespace ColorUtils

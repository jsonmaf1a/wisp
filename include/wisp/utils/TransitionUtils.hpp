#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace TransitionUtils
{

    static constexpr float smoothstep(float t)
    {
        return t * t * (3.f - 2.f * t);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    static constexpr sf::Vector2<T> lerp(sf::Vector2<T> a, sf::Vector2<T> b,
                                         float t)
    {
        return a + (b - a) * t;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    static constexpr sf::Vector2<T> smoothLerp(sf::Vector2<T> a,
                                               sf::Vector2<T> b, float t)
    {
        t = smoothstep(t);
        return lerp(a, b, t);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    static constexpr sf::Vector2<T> expLerp(sf::Vector2<T> a, sf::Vector2<T> b,
                                            float t, float k = 10.f)
    {
        t = (1.f - std::exp(-k * t));
        return lerp(a, b, t);
    }
} // namespace TransitionUtils

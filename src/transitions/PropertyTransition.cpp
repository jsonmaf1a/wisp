#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <wisp/transitions/PropertyTransition.hpp>
#include <wisp/utils/TransitionUtils.hpp>

namespace wisp
{
    template <>
    float PropertyTransition<float>::interpolate(const float &start, const float &end, float t)
    {
        return start + (end - start) * t;
    }

    template <> int PropertyTransition<int>::interpolate(const int &start, const int &end, float t)
    {
        return start + (end - start) * t;
    }

    template <>
    sf::Color PropertyTransition<sf::Color>::interpolate(const sf::Color &start,
                                                         const sf::Color &end, float t)
    {
        return sf::Color(start.r + (end.r - start.r) * t, start.g + (end.g - start.g) * t,
                         start.b + (end.b - start.b) * t, start.a + (end.a - start.a) * t);
    }

    template <>
    sf::Vector2i PropertyTransition<sf::Vector2i>::interpolate(const sf::Vector2i &start,
                                                               const sf::Vector2i &end, float t)
    {
        return sf::Vector2i(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t);
    }

    template <>
    sf::Vector2f PropertyTransition<sf::Vector2f>::interpolate(const sf::Vector2f &start,
                                                               const sf::Vector2f &end, float t)
    {
        return TransitionUtils::expLerp(start, end, t);
    }
} // namespace wisp

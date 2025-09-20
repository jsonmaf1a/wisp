#pragma once

#include <SFML/Window/Event.hpp>

namespace EventUtils
{
    static constexpr bool isMouseEvent(const sf::Event &event)
    {
        return event.is<sf::Event::MouseMoved>() ||
               event.is<sf::Event::MouseButtonPressed>() ||
               event.is<sf::Event::MouseButtonReleased>();
    }

    static constexpr bool isLeftClickEvent(const sf::Event &event)
    {
        auto mouseClickEvent = event.getIf<sf::Event::MouseButtonPressed>();
        return mouseClickEvent &&
               mouseClickEvent->button == sf::Mouse::Button::Left;
    }
} // namespace EventUtils

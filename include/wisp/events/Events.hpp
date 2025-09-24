#pragma once

#include "../core/managers/CursorManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace wisp
{
    struct EventContext
    {
        const sf::Event &event;
        sf::RenderWindow &window;
        CursorManager &cursorManager;
    };

    enum class EventResult
    {
        Ignored,
        Handled, //  NOTE: event was handled, but can continue propagation
        Consumed //  NOTE: event was handled and should stop propagation
    };
} // namespace wisp

#include <wisp/core/managers/CursorManager.hpp>

namespace wisp
{
    CursorManager::CursorManager(sf::RenderWindow &window)
        : window(window)
    {
        handCursor =
            std::make_unique<sf::Cursor>(*sf::Cursor::createFromSystem(sf::Cursor::Type::Hand));
        if(!handCursor)
            throw std::runtime_error("Failed to load hand cursor");

        defaultCursor =
            std::make_unique<sf::Cursor>(*sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow));
        if(!defaultCursor)
            throw std::runtime_error("Failed to load default cursor");
    }

    void CursorManager::setHandCursor() { window.setMouseCursor(*handCursor); }
    void CursorManager::resetCursor() { window.setMouseCursor(*defaultCursor); }
} // namespace wisp

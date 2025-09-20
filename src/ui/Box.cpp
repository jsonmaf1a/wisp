#include "wisp/ui/Box.hpp"
#include "wisp/utils/PositionUtils.hpp"
#include <print>

void Box::drawSelf(sf::RenderWindow &window)
{
    sf::RectangleShape panelViewBg;

    panelViewBg.setSize(bounds.size);
    panelViewBg.setPosition({0, 0});
    panelViewBg.setFillColor({255, 0, 125, 255});

    window.draw(panelViewBg);
}

EventResult Box::handleSelfEvent(const EventContext &eventCtx)
{
    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();

        auto normalizedPosition = PositionUtils::normalizePosition(
            mouseMoved->position, eventCtx.window);

        if(viewportContains(normalizedPosition))
        {
            std::println("{} x: {}\ty: {}", "\033[31m[mousemove]\033[0m",
                         mouseMoved->position.x, mouseMoved->position.y);

            return EventResult::Handled;
        }
    }

    return EventResult::Ignored;
}

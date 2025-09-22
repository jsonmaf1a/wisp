#include "wisp/ui/Box.hpp"
#include "wisp/utils/PositionUtils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <print>

void Box::drawSelf(sf::RenderWindow &window)
{
    sf::RectangleShape bg;
    bg.setSize(bounds.size);
    bg.setPosition(bounds.position);
    bg.setFillColor({255, 255, 255, 10});

    window.draw(bg);

#ifdef DEBUG
    drawBoundingBox(window);
#endif // DEBUG
}

EventResult Box::handleSelfEvent(const EventContext &eventCtx)
{
#ifdef DEBUG
    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();

        auto normalizedPosition =
            PositionUtils::normalizePosition(mouseMoved->position, eventCtx.window);

        if(contains(normalizedPosition))
        {
            std::println("{} x: {}\ty: {}", "\033[31m[mousemove]\033[0m", mouseMoved->position.x,
                         mouseMoved->position.y);

            return EventResult::Handled;
        }
    }

    if(eventCtx.event.is<sf::Event::MouseButtonPressed>())
    {
        const auto mouseBtn = eventCtx.event.getIf<sf::Event::MouseButtonPressed>()->button;
        if(mouseBtn == sf::Mouse::Button::Left)
        {
            printChildren();
            return EventResult::Handled;
        }
    }
#endif // DEBUG

    return EventResult::Ignored;
}

void Box::arrangeChildren()
{
    auto bounds = getBounds();

    bool isRow = (flexDirection == FlexDirection::Row);

    auto getMainAxis = [isRow](const sf::Vector2f &v) -> float { return isRow ? v.x : v.y; };
    auto getCrossAxis = [isRow](const sf::Vector2f &v) -> float { return isRow ? v.y : v.x; };

    float availableMain = getMainAxis(bounds.size);

    std::vector<FlexLine> lines;
    FlexLine currentLine;

    for(auto &child : children)
    {
        auto childSize = child->getBounds().size;
        float childMain = getMainAxis(childSize);
        float childCross = getCrossAxis(childSize);

        if(!currentLine.items.empty() && currentLine.totalMainSize + childMain > availableMain)
        {
            lines.push_back(currentLine);
            currentLine = FlexLine{};
        }
        currentLine.items.push_back(child);
        currentLine.totalMainSize += childMain;
        currentLine.maxCrossSize = std::max(currentLine.maxCrossSize, childCross);
    }

    if(!currentLine.items.empty())
    {
        lines.push_back(currentLine);
    }

    float crossPos = getCrossAxis(bounds.position);
    for(auto &line : lines)
    {
        float mainPos = getMainAxis(bounds.position);
        for(auto &child : line.items)
        {
            auto childSize = child->getBounds().size;
            float childMain = getMainAxis(childSize);
            float childCross = getCrossAxis(childSize);

            sf::Vector2f childPos;
            childPos.x = isRow ? mainPos : crossPos;
            childPos.y = isRow ? crossPos : mainPos;

            sf::Vector2f childSz;
            childSz.x = isRow ? childMain : childCross;
            childSz.y = isRow ? childCross : childMain;

            child->setBounds(sf::FloatRect(childPos, childSz));
            mainPos += childMain;
        }
        crossPos += line.maxCrossSize;
    }
}

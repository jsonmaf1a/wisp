#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <print>
#include <wisp/ui/Box.hpp>
#include <wisp/utils/EventUtils.hpp>

namespace wisp
{
    void Box::drawSelf(sf::RenderWindow &window)
    {
        sf::RectangleShape bg;
        bg.setSize(bounds.size);
        bg.setPosition(bounds.position);
        bg.setFillColor({255, 255, 255, 30});

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

            sf::Vector2f mousePosF(static_cast<float>(mouseMoved->position.x),
                                   static_cast<float>(mouseMoved->position.y));

            if(contains(mousePosF))
            {
                std::print("\r{} x: {}\ty: {}   ", "\033[31m[mousemove]\033[0m",
                           mouseMoved->position.x, mouseMoved->position.y);
                std::cout.flush();

                return EventResult::Consumed;
            }
        }

        if(EventUtils::isLeftClickEvent(eventCtx.event))
        {
            auto mouseClick = eventCtx.event.getIf<sf::Event::MouseButtonPressed>();
            sf::Vector2f mousePosF(static_cast<float>(mouseClick->position.x),
                                   static_cast<float>(mouseClick->position.y));

            if(contains(mousePosF))
            {
                std::println("Clicked on: {}\t{}x{} at {}x{}", id, bounds.size.x, bounds.size.y,
                             bounds.position.x, bounds.position.y);

                if(hasChildren())
                    printChildren();

                return EventResult::Consumed;
            }
        }
#endif // DEBUG

        return EventResult::Ignored;
    }

    void Box::arrangeChildren()
    {
        const auto bounds = getBounds();
        const bool isRow = (direction == Flex::Direction::Type::Row);
        auto lines = createFlexLines(bounds.size, isRow);

        positionChildrenInLines(lines, bounds.position, isRow);
        justifyContent(lines, bounds.size, isRow);
        alignItems(lines, bounds.size, isRow);
    }

    std::vector<Flex::FlexLine> Box::createFlexLines(const sf::Vector2f &containerSize,
                                                     bool isRow) const
    {
        const float availableMainSize = getMainAxisValue(containerSize, isRow);

        std::vector<Flex::FlexLine> lines;
        Flex::FlexLine currentLine;

        for(const auto &child : children)
        {
            const auto childSize = child->getBounds().size;
            const float childMainSize = getMainAxisValue(childSize, isRow);
            const float childCrossSize = getCrossAxisValue(childSize, isRow);

            if(shouldWrapToNewLine(currentLine, childMainSize, availableMainSize))
            {
                lines.push_back(std::move(currentLine));
                currentLine = Flex::FlexLine{};
            }

            addChildToLine(currentLine, child, childMainSize, childCrossSize);
        }

        if(!currentLine.items.empty())
        {
            lines.push_back(std::move(currentLine));
        }

        return lines;
    }

    void Box::positionChildrenInLines(const std::vector<Flex::FlexLine> &lines,
                                      const sf::Vector2f &containerPos, bool isRow)
    {
        float crossPos = getCrossAxisValue(containerPos, isRow);

        for(const auto &line : lines)
        {
            positionChildrenInLine(line, containerPos, crossPos, isRow);
            crossPos += line.maxCrossSize;
        }
    }

    void Box::positionChildrenInLine(const Flex::FlexLine &line, const sf::Vector2f &containerPos,
                                     float crossPos, bool isRow)
    {
        float mainPos = getMainAxisValue(containerPos, isRow);

        for(const auto &child : line.items)
        {
            const auto childSize = child->getBounds().size;
            const auto childPosition = createChildPosition(mainPos, crossPos, isRow);

            child->setBounds(sf::FloatRect(childPosition, childSize));
            mainPos += getMainAxisValue(childSize, isRow);
        }
    }

    void Box::justifyContent(std::vector<Flex::FlexLine> &lines, const sf::Vector2f &containerSize,
                             bool isRow)
    {
        const float availableMainSize = getMainAxisValue(containerSize, isRow);
        auto strategy = Flex::Justification::createStrategy(justify);

        for(auto &line : lines)
        {
            line.remainingSpace = availableMainSize - line.totalMainSize;
            if(line.remainingSpace > 0)
            {
                strategy->apply(line, isRow);
            }
        }
    }

    void Box::alignItems(std::vector<Flex::FlexLine> &lines, const sf::Vector2f &containerSize,
                         bool isRow)
    {
        // const float availableMainSize = getMainAxisValue(containerSize, isRow);
        // auto strategy = Flex::Alignment::createStrategy(align);
        //
        // for(auto &line : lines)
        // {
        //     line.remainingSpace = availableMainSize - line.totalMainSize;
        //     if(line.remainingSpace > 0)
        //     {
        //         strategy->apply(line, isRow);
        //     }
        // }
    }

    float Box::getMainAxisValue(const sf::Vector2f &vector, bool isRow) const
    {
        return isRow ? vector.x : vector.y;
    }

    float Box::getCrossAxisValue(const sf::Vector2f &vector, bool isRow) const
    {
        return isRow ? vector.y : vector.x;
    }

    sf::Vector2f Box::createChildPosition(float mainPos, float crossPos, bool isRow) const
    {
        return isRow ? sf::Vector2f(mainPos, crossPos) : sf::Vector2f(crossPos, mainPos);
    }

    bool Box::shouldWrapToNewLine(const Flex::FlexLine &currentLine, float childMainSize,
                                  float availableMainSize) const
    {
        return !currentLine.items.empty() &&
               (currentLine.totalMainSize + childMainSize > availableMainSize);
    }

    void Box::addChildToLine(Flex::FlexLine &line, const std::shared_ptr<Component> &child,
                             float childMainSize, float childCrossSize) const
    {
        line.items.push_back(child);
        line.totalMainSize += childMainSize;
        line.maxCrossSize = std::max(line.maxCrossSize, childCrossSize);
    }

    void Box::setWidth(float width)
    {
        if(width <= 1.f)
        {
            if(auto parentLock = parent.lock())
            {
                bounds.size.x = parentLock->getBounds().size.x * width;
                return;
            }
        }

        bounds.size.x = width;
    }
    const float Box::getWidth() { return bounds.size.x; }

    void Box::setHeight(float height)
    {

        if(height <= 1.f)
        {
            if(auto parentLock = parent.lock())
            {
                bounds.size.y = parentLock->getBounds().size.y * height;
                return;
            }
        }

        bounds.size.y = height;
    }
    const float Box::getHeight() { return bounds.size.y; }

    void Box::setJustification(Flex::Justification::Type type) { justify = type; }
    const Flex::Justification::Type Box::getJustification() { return justify; }
    void Box::setAlignment(Flex::Alignment::Type type) { align = type; }
    const Flex::Alignment::Type Box::getAlignment() { return align; }
    void Box::setDirection(Flex::Direction::Type type) { direction = type; }
    const Flex::Direction::Type Box::getDirection() { return direction; }

    const char *Box::getName() const { return "Box"; };
} // namespace wisp

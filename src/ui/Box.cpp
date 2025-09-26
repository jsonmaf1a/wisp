#include "wisp/common/Dimensions.hpp"
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

    std::shared_ptr<Box> Box::attachTo(std::shared_ptr<Component> parent)
    {
        parent->addChild(std::static_pointer_cast<Box>(shared_from_this()));
        return std::static_pointer_cast<Box>(shared_from_this());
    }

    std::shared_ptr<Box> Box::detach()
    {
        parent.reset();
        return std::static_pointer_cast<Box>(shared_from_this());
    };

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
        if(!hasChildren())
            return;

        if(availableSpace.x <= 0 || availableSpace.y <= 0)
        {
            availableSpace = bounds.size;
        }

        computedSize.x = sizeSpec.width.resolve(availableSpace.x);
        computedSize.y = sizeSpec.height.resolve(availableSpace.y);
        computedSize.x = std::max(0.0f, computedSize.x);
        computedSize.y = std::max(0.0f, computedSize.y);
        bounds.size = computedSize;
        std::println("{}x{}", bounds.size.x, bounds.size.y);

        const bool isRow = (direction == Flex::Direction::Row);
        auto lines = createFlexLines(computedSize, isRow);

        positionChildrenInLines(lines, bounds.position, isRow);
        justifyContent(lines, computedSize, isRow);
        alignItems(lines, computedSize, isRow);
    }

    std::vector<Flex::FlexLine> Box::createFlexLines(const sf::Vector2f &containerSize,
                                                     bool isRow) const
    {
        const float availableMainSize = getMainAxisValue(containerSize, isRow);

        std::vector<Flex::FlexLine> lines;
        Flex::FlexLine currentLine;

        for(const auto &child : children)
        {
            sf::Vector2f childSize{child->sizeSpec.width.resolve(containerSize.x),
                                   child->sizeSpec.height.resolve(containerSize.y)};

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
            // const auto childSize = child->getBounds().size;
            sf::Vector2f childSize{child->sizeSpec.width.resolve(computedSize.x),
                                   child->sizeSpec.height.resolve(computedSize.y)};
            const auto childPosition = createChildPosition(mainPos, crossPos, isRow);

            child->setBounds(sf::FloatRect(childPosition, childSize));
            child->availableSpace = {computedSize.x, computedSize.y};

            if(child->getIsDirty())
            {
                child->arrangeChildren();
            }
            mainPos += getMainAxisValue(childSize, isRow);
        }
    }

    void Box::justifyContent(std::vector<Flex::FlexLine> &lines, const sf::Vector2f &containerSize,
                             bool isRow)
    {
        const float availableMainSize = getMainAxisValue(containerSize, isRow);
        auto strategy = Flex::createJustificationStrategy(justify);

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
        // TODO: align items
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

    const float Box::getWidth() { return bounds.size.x; }
    const float Box::getHeight() { return bounds.size.y; }
    const Flex::Justification Box::getJustification() { return justify; }
    const Flex::Alignment Box::getAlignment() { return align; }
    const Flex::Direction Box::getDirection() { return direction; }

    std::shared_ptr<Box> Box::setWidth(float width, wisp::Size::Unit unit)
    {
        // availableSpace.x = width;
        sizeSpec.width = {width, unit};
        isDirty = true;
        if(auto p = parent.lock())
            p->setIsDirty(true);

        return std::static_pointer_cast<Box>(shared_from_this());
    }
    std::shared_ptr<Box> Box::setFullWidth()
    {
        setWidth(1, wisp::Size::Unit::Percent);
        return std::static_pointer_cast<Box>(shared_from_this());
    }

    std::shared_ptr<Box> Box::setHeight(float height, wisp::Size::Unit unit)
    {
        // availableSpace.y = height;
        sizeSpec.height = {height, unit};
        isDirty = true;
        if(auto p = parent.lock())
            p->setIsDirty(true);
        return std::static_pointer_cast<Box>(shared_from_this());
    }
    std::shared_ptr<Box> Box::setFullHeight()
    {
        setHeight(1, wisp::Size::Unit::Percent);
        return std::static_pointer_cast<Box>(shared_from_this());
    }

    std::shared_ptr<Box> Box::setSize(sf::Vector2f size, wisp::Size::Unit unit)
    {
        setWidth(size.x, unit);
        setHeight(size.y, unit);
        return std::static_pointer_cast<Box>(shared_from_this());
    }

    std::shared_ptr<Box> Box::setDirection(Flex::Direction direction)
    {
        this->direction = direction;
        isDirty = true;
        return std::static_pointer_cast<Box>(shared_from_this());
    }
    std::shared_ptr<Box> Box::setJustification(Flex::Justification justify)
    {
        this->justify = justify;
        isDirty = true;
        return std::static_pointer_cast<Box>(shared_from_this());
    }
    std::shared_ptr<Box> Box::setAlignment(Flex::Alignment align)
    {
        this->align = align;
        isDirty = true;
        return std::static_pointer_cast<Box>(shared_from_this());
    }
    std::shared_ptr<Box> Box::setAvailableSpace(sf::Vector2f size)
    {
        this->availableSpace = size;
        isDirty = true;
        return std::static_pointer_cast<Box>(shared_from_this());
    }

    const char *Box::getName() const { return "Box"; };
} // namespace wisp

#pragma once

#include "../core/Component.hpp"
#include "../core/flex/Flex.hpp"
#include "wisp/common/Dimensions.hpp"
#include <memory>
#include <vector>

namespace wisp
{
    class Box : public Component
    {

      public:
        static std::shared_ptr<Box> create(/* const sf::FloatRect &bounds = {{0, 0}, {0, 0}} */)
        {
            return std::make_shared<Box>(/* bounds */);
        }

        std::shared_ptr<Box> setSize(sf::Vector2f size, wisp::Size::Unit unit = Size::Unit::Pixels);
        std::shared_ptr<Box> setWidth(float width, wisp::Size::Unit unit = Size::Unit::Pixels);
        std::shared_ptr<Box> setFullWidth();
        std::shared_ptr<Box> setHeight(float width, wisp::Size::Unit unit = Size::Unit::Pixels);
        std::shared_ptr<Box> setFullHeight();
        std::shared_ptr<Box> setDirection(Flex::Direction direction);
        std::shared_ptr<Box> setJustification(Flex::Justification justify);
        std::shared_ptr<Box> setAlignment(Flex::Alignment align);
        std::shared_ptr<Box> setAvailableSpace(sf::Vector2f size);
        std::shared_ptr<Box> attachTo(std::shared_ptr<Component> parent);
        std::shared_ptr<Box> detach();

        Box(sf::FloatRect bounds)
            : Component(bounds)
        {}

        Box()
            : Component()
            , direction(Flex::Direction::Row)
            , justify(Flex::Justification::Start)
            , align(Flex::Alignment::Start)
        {
            sizeSpec.width = {1.f, wisp::Size::Unit::Percent};
            sizeSpec.height = {1.f, wisp::Size::Unit::Percent};
        }
        Box(Flex::Direction direction, Flex::Justification justification, Flex::Alignment alignment)
            : Component()
            , direction(direction)
            , justify(justification)
            , align(alignment)
        {
            sizeSpec.width = {1.f, wisp::Size::Unit::Percent};
            sizeSpec.height = {1.f, wisp::Size::Unit::Percent};
        }
        ~Box() = default;

        const float getWidth();
        const float getHeight();
        const Flex::Justification getJustification();
        const Flex::Alignment getAlignment();
        const Flex::Direction getDirection();

        virtual void arrangeChildren() override final;

      protected:
        Flex::Direction direction;
        Flex::Justification justify;
        Flex::Alignment align;

        virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;
        virtual const char *getName() const override;
        virtual void drawSelf(sf::RenderWindow &window) override;

      private:
        std::vector<Flex::FlexLine> createFlexLines(const sf::Vector2f &containerSize,
                                                    bool isRow) const;
        void positionChildrenInLines(const std::vector<Flex::FlexLine> &lines,
                                     const sf::Vector2f &containerPos, bool isRow);
        void positionChildrenInLine(const Flex::FlexLine &line, const sf::Vector2f &containerPos,
                                    float crossPos, bool isRow);

        void justifyContent(std::vector<Flex::FlexLine> &lines, const sf::Vector2f &containerSize,
                            bool isRow);
        void alignItems(std::vector<Flex::FlexLine> &lines, const sf::Vector2f &containerSize,
                        bool isRow);
        float getMainAxisValue(const sf::Vector2f &vector, bool isRow) const;
        float getCrossAxisValue(const sf::Vector2f &vector, bool isRow) const;
        sf::Vector2f createChildPosition(float mainPos, float crossPos, bool isRow) const;
        bool shouldWrapToNewLine(const Flex::FlexLine &currentLine, float childMainSize,
                                 float availableMainSize) const;
        void addChildToLine(Flex::FlexLine &line, const std::shared_ptr<Component> &child,
                            float childMainSize, float childCrossSize) const;
    };
} // namespace wisp

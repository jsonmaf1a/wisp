#pragma once

#include "../core/Component.hpp"
#include "../core/flex/Flex.hpp"
#include <memory>
#include <vector>

namespace wisp
{
    class Box : public Component
    {
      public:
        Box(sf::RenderWindow &target, sf::FloatRect bounds)
            : Component(bounds)
            , availableSpace(bounds.size)
        {}
        Box(sf::RenderWindow &target)
            : Component()
        {
            // WIP!!!
            sf::FloatRect bounds({0.f, 0.f}, {100.f, 100.f});
            setBounds(bounds);
            availableSpace = bounds.size;
        }
        ~Box() = default;

        virtual EventResult handleSelfEvent(const EventContext &eventCtx) override final;
        virtual void arrangeChildren() override final;

        Box *setWidth(float width);
        const float getWidth();
        Box *setHeight(float height);
        const float getHeight();

      protected:
        sf::Vector2f availableSpace;
        Flex::Direction::Type flexDirection = Flex::Direction::Type::Row;
        Flex::Justification::Type justify = Flex::Justification::Type::Start;
        Flex::Alignment::Type align = Flex::Alignment::Type::Start;

        virtual const char *getName() const override final;
        virtual void drawSelf(sf::RenderWindow &window) override final;

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

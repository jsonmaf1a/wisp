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
        Box(sf::FloatRect bounds)
            : Component(bounds)
            , availableSpace(bounds.size)
        {}
        Box()
            : Component()
        {
            // WIP!!!
            sf::FloatRect bounds({0.f, 0.f}, {100.f, 100.f});
            setBounds(bounds);
            availableSpace = bounds.size;
        }
        Box(Flex::Direction::Type direction, Flex::Justification::Type justification,
            Flex::Alignment::Type alignment)
            : Component()
            , availableSpace({0, 0})
            , direction(direction)
            , justify(justification)
            , align(alignment)
        {
            sf::FloatRect bounds({0.f, 0.f}, {0.f, 0.f});
            setBounds(bounds);
            availableSpace = bounds.size;
        }
        ~Box() = default;

        void setWidth(float width);
        const float getWidth();
        void setHeight(float height);
        const float getHeight();
        void setJustification(Flex::Justification::Type type);
        const Flex::Justification::Type getJustification();
        void setAlignment(Flex::Alignment::Type type);
        const Flex::Alignment::Type getAlignment();
        void setDirection(Flex::Direction::Type type);
        const Flex::Direction::Type getDirection();

        virtual void arrangeChildren() override final;

      protected:
        sf::Vector2f availableSpace;
        Flex::Direction::Type direction = Flex::Direction::Type::Row;
        Flex::Justification::Type justify = Flex::Justification::Type::Start;
        Flex::Alignment::Type align = Flex::Alignment::Type::Start;

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

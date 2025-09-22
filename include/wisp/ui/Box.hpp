#pragma once

#include "../core/Component.hpp"
#include "wisp/core/Component.hpp"
#include <memory>
#include <vector>
#include <wisp/common/Flex.hpp>

struct FlexLine
{
    std::vector<std::shared_ptr<Component>> items;
    float totalMainSize = 0.f;
    float maxCrossSize = 0.f;
};

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

  protected:
    sf::Vector2f availableSpace;
    FlexDirection flexDirection = FlexDirection::Row;
    FlexJustification justify = FlexJustification::Start;
    FlexAlignment align = FlexAlignment::Start;

    virtual void drawSelf(sf::RenderWindow &window) override final;
};

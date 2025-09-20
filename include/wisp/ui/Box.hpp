#pragma once

#include "wisp/core/Component.hpp"

class Box : public Component
{

  protected:
    virtual void drawSelf(sf::RenderWindow &window) override;

  public:
    Box(sf::RenderWindow &target, sf::FloatRect bounds, sf::FloatRect viewport)
        : Component(bounds)
    {
        enableView();
        view->setViewport(viewport);
    }
    ~Box() = default;

    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;
};

#pragma once

#include "../Component.hpp"
#include "../managers/EventDispatcher.hpp"
#include <concepts>
#include <memory>
#include <wisp/ui/Box.hpp>

class UIManager
{
  public:
    UIManager(EventDispatcher &dispatcher)
        : dispatcher(dispatcher) {};

    void addComponent(std::shared_ptr<Component> component);
    template <std::derived_from<Component>... Components>
    void addComponents(const std::shared_ptr<Components> &...components)
    {
        (addComponent(components), ...);
    }
    void removeComponent(std::shared_ptr<Component> component);
    void handleEvent(const EventContext &event);
    void draw(sf::RenderWindow &window);

    std::shared_ptr<Box> rootBox;
    void setRootBox(std::shared_ptr<Box>);

  private:
    EventDispatcher &dispatcher;
    sf::Clock clock;

    void adjustComponent(std::shared_ptr<Component> component);
};

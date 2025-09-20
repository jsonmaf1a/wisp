#pragma once

#include "../Component.hpp"
#include "../managers/EventDispatcher.hpp"
#include <memory>
#include <vector>

class UIManager
{
  public:
    UIManager(EventDispatcher &dispatcher)
        : dispatcher(dispatcher) {};

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);
    void handleEvent(const EventContext &event);
    void draw(sf::RenderWindow &window);

  private:
    std::vector<std::shared_ptr<Component>> rootComponents;
    EventDispatcher &dispatcher;
    sf::Clock clock;
};

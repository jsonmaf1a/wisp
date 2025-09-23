#include <wisp/core/managers/TransitionManager.hpp>
#include <wisp/core/managers/UIManager.hpp>

void UIManager::addComponent(std::shared_ptr<Component> component)
{
    rootBox->addChild(component);
    dispatcher.registerListener(component);
}

void UIManager::removeComponent(std::shared_ptr<Component> component)
{
    dispatcher.unregisterListener(component);
    rootBox->removeChild(component);
}

void UIManager::handleEvent(const EventContext &event) { rootBox->handleEvent(event); }

void UIManager::draw(sf::RenderWindow &window)
{
    float dt = clock.restart().asSeconds();
    TransitionManager::update(dt);

    rootBox->draw(window);
}

void UIManager::setRootBox(std::shared_ptr<Box> box)
{
    rootBox = box;
    dispatcher.registerListener(rootBox);
}

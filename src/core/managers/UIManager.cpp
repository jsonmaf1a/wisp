#include <wisp/core/managers/TransitionManager.hpp>
#include <wisp/core/managers/UIManager.hpp>

void UIManager::addComponent(std::shared_ptr<Component> component)
{
    rootComponents.push_back(component);
    dispatcher.registerListener(component);
}

void UIManager::removeComponent(std::shared_ptr<Component> component)
{
    dispatcher.unregisterListener(component);
    rootComponents.erase(
        std::remove(rootComponents.begin(), rootComponents.end(), component),
        rootComponents.end());
}

void UIManager::handleEvent(const EventContext &event)
{
    for(auto it = rootComponents.rbegin(); it != rootComponents.rend(); ++it)
    {
        EventResult result = (*it)->handleEvent(event);
        if(result == EventResult::Consumed)
        {
            break;
        }
    }
}

void UIManager::draw(sf::RenderWindow &window)
{
    for(auto &component : rootComponents)
    {
        float dt = clock.restart().asSeconds();
        TransitionManager::update(dt);

        component->draw(window);
    }
}

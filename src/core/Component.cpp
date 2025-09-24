#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <print>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wisp/core/Component.hpp>

namespace wisp
{
    void Component::addChild(std::shared_ptr<Component> child)
    {
        child->parent = weak_from_this();
        children.push_back(child);

        arrangeChildren();
    }

    void Component::removeChild(std::shared_ptr<Component> child)
    {
        auto it = std::find_if(children.begin(), children.end(), [&](const auto &currentChild) {
            return currentChild->id == child->id;
        });

        if(it != children.end())
        {
            (*it)->parent.reset();
            children.erase(it);
        }

        arrangeChildren();
    }

    void Component::draw(sf::RenderWindow &window)
    {
        if(!visible)
            return;

        drawSelf(window);

        for(auto &child : children)
        {
            child->draw(window);
        }
    }

    EventResult Component::handleEvent(const EventContext &event)
    {
        if(!visible || !enabled)
            return EventResult::Ignored;

        // First, give children a chance to handle the event (in reverse order
        // for proper z-ordering)
        for(auto it = children.rbegin(); it != children.rend(); ++it)
        {
            EventResult result = (*it)->handleEvent(event);
            if(result == EventResult::Consumed)
            {
                return EventResult::Consumed;
            }
        }

        return handleSelfEvent(event);
    }

    void Component::setVisible(bool visible) { this->visible = visible; }

    bool Component::isVisible() const { return visible; }

    void Component::setEnabled(bool enabled) { this->enabled = enabled; }

    bool Component::isEnabled() const { return enabled; }

    void Component::setBounds(const sf::FloatRect &bounds) { this->bounds = bounds; }

    const sf::FloatRect &Component::getBounds() const { return bounds; }

    void Component::printChildren() const
    {
        auto _children = this->children;
        std::sort(_children.begin(), _children.end(),
                  [](const auto &a, const auto &b) { return a->id < b->id; });

        std::println("\033[32m[child ID]\t[name]\t\t[size and position]\033[0m");
        for(auto &child : _children)
        {
            std::println("\033[33m[{}]\033[0m\t\t{}\t\t{}x{} at {}x{}", child->id, child->getName(),
                         child->bounds.size.x, child->bounds.size.y, child->bounds.position.x,
                         child->bounds.position.y);
        }
        std::print("\n");
    }

    void Component::drawBoundingBox(sf::RenderWindow &window)
    {
        sf::RectangleShape boundingBox;
        boundingBox.setSize(bounds.size);
        boundingBox.setPosition(bounds.position);
        boundingBox.setFillColor(sf::Color::Transparent);
        boundingBox.setOutlineColor(sf::Color::Red);
        boundingBox.setOutlineThickness(-1.f);

        window.draw(boundingBox);
    }

    bool Component::hasChildren() const { return !children.empty(); }
} // namespace wisp

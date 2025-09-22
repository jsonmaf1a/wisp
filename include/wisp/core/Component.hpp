#pragma once

#include "../events/EventHandler.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

class Component : public EventHandler, public std::enable_shared_from_this<Component>
{
  protected:
    Component(sf::FloatRect bounds)
        : id(nextID++)
        , bounds(bounds) {};
    Component(sf::Vector2f size)
        : id(nextID++)
        , bounds(sf::FloatRect({0, 0}, size)) {};
    Component()
        : id(nextID++)
        , bounds(sf::FloatRect({0, 0}, {0, 0})) {};

    virtual ~Component() = default;

    sf::FloatRect bounds;
    std::vector<std::shared_ptr<Component>> children;

    unsigned int id;
    bool visible = true;
    bool enabled = true;
    std::weak_ptr<Component> parent;

    virtual void drawSelf(sf::RenderWindow &window) = 0;
    void drawBoundingBox(sf::RenderWindow &widnow);
    virtual void arrangeChildren() = 0; // TODO: default `arrangeChildren` impl

  public:
    virtual void draw(sf::RenderWindow &window);

    EventResult handleEvent(const EventContext &event) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx)
    {
        return EventResult::Ignored;
    }

    void addChild(std::shared_ptr<Component> child);
    void removeChild(std::shared_ptr<Component> child);
    bool hasChildren() const;
    void printChildren() const;
    void setVisible(bool visible);
    bool isVisible() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setBounds(const sf::FloatRect &bounds);
    const sf::FloatRect &getBounds() const;

    template <typename T> bool contains(const sf::Vector2<T> &position) const
    {
        return visible && enabled && bounds.contains(sf::Vector2f(position));
    }

  private:
    static inline int nextID = 0;
};

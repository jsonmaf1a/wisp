#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wisp/core/Component.hpp>

bool almostEqual(float a, float b, float epsilon = 0.001f)
{
    return std::abs(a - b) < epsilon;
}

// sf::FloatRect Component::createViewport()
// {
//     sf::Vector2f parentSize = LayoutConfig::WindowSize;
//     sf::Vector2f parentPosition = sf::Vector2f{0.f, 0.f};
//
//     float siblingOffsetX = 0.f;
//     float siblingOffsetY = 0.f;
//
//     if(auto parentLock = parent.lock())
//     {
//         parentSize = parentLock->getBounds().size;
//         parentPosition = parentLock->getBounds().position;
//
//         for(const auto sibling : parentLock->children)
//         {
//
//             if(sibling->id == this->id)
//                 break;
//
//             std::cout << sibling->getBounds().size.x << getBounds().size.x
//                       << "\n";
//
//             // if(sibling->getBounds().size.x == getBounds().size.x)
//             // {
//             //     siblingOffsetY += sibling->getBounds().size.y;
//             // }
//             // else
//
//             siblingOffsetX += sibling->getBounds().size.x;
//             if(siblingOffsetX > sibling->getBounds().size.x ||
//                almostEqual(siblingOffsetX, sibling->getBounds().size.x))
//             {
//                 siblingOffsetX = 0.f;
//                 siblingOffsetY += sibling->getBounds().size.y;
//             }
//         }
//     }
//
//     float relPosX =
//         (siblingOffsetX + getBounds().position.x - parentPosition.x) /
//         parentSize.x;
//     float relPosY =
//         (siblingOffsetY + getBounds().position.y - parentPosition.y) /
//         parentSize.y;
//     float relWidth = getBounds().size.x / parentSize.x;
//     float relHeight = getBounds().size.y / parentSize.y;
//
//     float xScaleFactor = parentSize.x / LayoutConfig::WindowSize.x;
//     relPosX *= xScaleFactor;
//     relWidth *= xScaleFactor;
//
//     float yScaleFactor = parentSize.y / LayoutConfig::WindowSize.y;
//     relPosY *= yScaleFactor;
//     relHeight *= yScaleFactor;
//
//     return sf::FloatRect({relPosX, relPosY}, {relWidth, relHeight});
// }

void Component::enableView(sf::View view)
{
    this->view = view;
    // this->view->setViewport(createViewport());
};

void Component::enableView()
{
    this->view = sf::View(bounds);
    // view->setViewport(createViewport());
};

void Component::addChild(std::shared_ptr<Component> child)
{
    child->parent = weak_from_this();
    children.push_back(child);
}

void Component::removeChild(std::shared_ptr<Component> child)
{
    auto it = std::find_if(children.begin(), children.end(),
                           [&](const auto &currentChild) {
                               return currentChild->id == child->id;
                           });

    if(it != children.end())
    {
        (*it)->parent.reset();
        children.erase(it);
    }
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

void Component::setBounds(const sf::FloatRect &bounds)
{
    this->bounds = bounds;
}

const sf::FloatRect &Component::getBounds() const { return bounds; }
const std::optional<sf::View> &Component::getView() const { return view; }

// void Component::setView(sf::View view) { this->view = view; };
// void Component::setView(sf::FloatRect bounds) { view = sf::View(bounds); };

void Component::printChildren() const
{

    auto _children = this->children;
    std::sort(_children.begin(), _children.end(),
              [](const auto &a, const auto &b) { return a->id < b->id; });

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    std::cout << "\n" << std::string(w.ws_col, '-') << std::endl;

    for(auto &child : _children)
    {
        std::cout << child->id << " ";
    }
    std::cout << "\n" << std::string(w.ws_col, '-') << std::endl;
}

#include <wisp/ui/Button.hpp>
#include <wisp/utils/EventUtils.hpp>

namespace wisp
{
    void Button::drawSelf(sf::RenderWindow &window)
    {
        drawBackground(window);
        drawLabel(window);
    }

    void Button::drawLabel(sf::RenderWindow &window)
    {
        sf::Text label(font, text, fontSize);
        label.setOrigin(label.getLocalBounds().position);
        label.setPosition(
            {bounds.position.x + bounds.size.x / 2.f - label.getGlobalBounds().size.x / 2.f,
             bounds.position.y + bounds.size.y / 2.f - label.getGlobalBounds().size.y / 2.f});
        label.setFillColor(foreground);

        sf::RectangleShape labelBounds(label.getLocalBounds().size);
        labelBounds.setOutlineColor(sf::Color::Blue);
        labelBounds.setOutlineThickness(1.0f);
        labelBounds.setFillColor(sf::Color({0, 0, 255, 40}));
        labelBounds.setPosition(bounds.position + bounds.size / 2.f -
                                label.getLocalBounds().size / 2.f);

        window.draw(label);
#ifdef DEBUG
        window.draw(labelBounds);
#endif // DEBUG
    }
    void Button::drawBackground(sf::RenderWindow &window)
    {
        auto bounds = getBounds();
        sf::RectangleShape rect(bounds.size);
        rect.setPosition(bounds.position);
        rect.setFillColor(background);

        sf::RectangleShape rectBounds({bounds.size.x - 2.f, bounds.size.y - 2.f});
        rectBounds.setOutlineColor(sf::Color::Black);
        rectBounds.setOutlineThickness(1.0f);
        rectBounds.setPosition(bounds.position);
        rectBounds.setFillColor(sf::Color::Transparent);

        sf::RectangleShape centerX({1.0f, bounds.size.y});
        centerX.setOutlineColor(sf::Color::Red);
        centerX.setOutlineThickness(0.5f);
        centerX.setFillColor(sf::Color::Red);
        centerX.setPosition({bounds.position.x + bounds.size.x / 2.f, bounds.position.y});

        sf::RectangleShape centerY({bounds.size.x, 1.0f});
        centerY.setOutlineColor(sf::Color::Red);
        centerY.setOutlineThickness(0.5f);
        centerY.setFillColor(sf::Color::Red);
        centerY.setPosition({bounds.position.x, bounds.position.y + bounds.size.y / 2.f});

        window.draw(rect);
#ifdef DEBUG
        window.draw(rectBounds);
        window.draw(centerX);
        window.draw(centerY);
#endif // DEBUG
    }

    EventResult Button::handleSelfEvent(const EventContext &eventCtx)
    {
        if(EventUtils::isLeftClickEvent(eventCtx.event))
        {
            auto mouseClick = eventCtx.event.getIf<sf::Event::MouseButtonPressed>();
            sf::Vector2f mousePosF(static_cast<float>(mouseClick->position.x),
                                   static_cast<float>(mouseClick->position.y));

            if(contains(mousePosF))
            {
                return onClick(eventCtx);
                return EventResult::Consumed;
            }
        }

        if(eventCtx.event.is<sf::Event::MouseMoved>())
        {
            const auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();

            sf::Vector2f mousePosF(static_cast<float>(mouseMoved->position.x),
                                   static_cast<float>(mouseMoved->position.y));

            if(contains(mousePosF))
            {
                eventCtx.cursorManager.setHandCursor();
                return EventResult::Consumed;
            }
            else
            {
                eventCtx.cursorManager.resetCursor();
            }
        }

        return EventResult::Ignored;
    };

    std::shared_ptr<Button> Button::setText(std::string text)
    {
        this->text = text;

        return std::static_pointer_cast<Button>(shared_from_this());
    }

    std::shared_ptr<Button> Button::setOnClick(
        std::function<EventResult(const EventContext &)> onClick)
    {
        this->onClick = onClick;
        return std::static_pointer_cast<Button>(shared_from_this());
    }

    const char *Button::getName() const { return "Button"; };

    // std::shared_ptr<Button>
} // namespace wisp

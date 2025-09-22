#pragma once

#include "../core/Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <functional>

class Button : public Component
{
  public:
    Button(sf::Vector2f size, std::string label, const sf::Font &font,
           unsigned int fontSize = 14)
        : Component(size)
        , text(label)
        , font(font)
        , fontSize(fontSize) {};
    ~Button() = default;

    void setText(std::string text);
    void setOnClick(std::function<EventResult(const EventContext &)> onClick);
    virtual void drawSelf(sf::RenderWindow &window) override final;
    virtual EventResult handleSelfEvent(
        const EventContext &eventCtx) override final;

  private:
    std::function<EventResult(const EventContext &)> onClick;
    std::string text;
    sf::Color background;
    sf::Color foreground;
    const sf::Font &font;
    unsigned int fontSize;

    void drawLabel(sf::RenderWindow &window);
    void drawBackground(sf::RenderWindow &window);
};

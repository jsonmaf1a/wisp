#pragma once

#include "../ui/Box.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace wisp
{
    class Button : public Box
    {
      public:
        static std::shared_ptr<Button> create(std::string label, sf::Font &font,
                                              unsigned int fontSize = 16)
        {
            return std::make_shared<Button>(label, font, fontSize);
        }

        Button(std::string label, sf::Font &font, unsigned int fontSize)
            : Box()
            , text(label)
            , font(font)
            , fontSize(fontSize) {};
        ~Button() = default;

        std::shared_ptr<Button> setText(std::string text);
        std::shared_ptr<Button> setOnClick(
            std::function<EventResult(const EventContext &)> onClick);
        virtual void drawSelf(sf::RenderWindow &window) override final;
        virtual EventResult handleSelfEvent(const EventContext &eventCtx) override final;

      private:
        std::function<EventResult(const EventContext &)> onClick;
        std::string text;
        sf::Color background = sf::Color::Magenta;
        sf::Color foreground = sf::Color::Black;
        sf::Font &font;
        unsigned int fontSize;

        void drawLabel(sf::RenderWindow &window);
        void drawBackground(sf::RenderWindow &window);

      protected:
        virtual const char *getName() const override final;
    };
} // namespace wisp

#include "config/LayoutConfig.hpp"
#include "wisp/core/flex/FlexJustification.hpp"
#include "wisp/ui/Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <print>
#include <wisp/core/Window.hpp>

int main()
{
    wisp::Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto box1 = std::make_shared<wisp::Box>(sf::FloatRect{{0, 0}, {375, 800}});
    auto box2 = std::make_shared<wisp::Box>();
    auto box3 = std::make_shared<wisp::Box>();
    auto box4 = std::make_shared<wisp::Box>();
    auto box5 = std::make_shared<wisp::Box>();
    auto box6 = std::make_shared<wisp::Box>();
    auto box7 = std::make_shared<wisp::Box>();

    sf::Font font;
    bool _ = font.openFromFile("/home/hapka/dev/chess-cpp/assets/fonts/static/Roboto-Regular.ttf");

    auto buttonJustifyEnd = std::make_shared<wisp::Button>("Justification::Center", font, 16);
    buttonJustifyEnd->setOnClick([&, buttonJustifyEnd, box1](const wisp::EventContext &eventCtx) {
        box1->setJustification(wisp::Flex::Justification::Type::Center);
        box1->arrangeChildren();

        return wisp::EventResult::Consumed;
    });

    auto buttonJustifySBetween =
        std::make_shared<wisp::Button>("Justification::SpaceBetween", font, 16);
    buttonJustifySBetween->setOnClick(
        [&, buttonJustifySBetween, box1](const wisp::EventContext &eventCtx) {
            box1->setJustification(wisp::Flex::Justification::Type::SpaceBetween);
            box1->arrangeChildren();

            return wisp::EventResult::Consumed;
        });

    box1->addChildren(box2, box3, box4, box5, box6);
    box1->setDirection(wisp::Flex::Direction::Type::Row);
    box1->setJustification(wisp::Flex::Justification::Type::End);

    box2->setWidth(125.f);
    box2->setHeight(50.f);
    box3->setWidth(125.f);
    box3->setHeight(50.f);
    box4->setWidth(200.f);
    box4->setHeight(50.f);
    box5->setWidth(65.f);
    box5->setHeight(50.f);
    box6->setWidth(269.8f);
    box6->setHeight(20.f);

    ui.addComponents(box1, box7);

    box7->setWidth(1.f);
    box7->setHeight(1.f);
    box7->addChildren(buttonJustifyEnd, buttonJustifySBetween);
    box7->setDirection(wisp::Flex::Direction::Type::Column);
    box7->setJustification(wisp::Flex::Justification::Type::Start);
    buttonJustifyEnd->setWidth(300.f);
    buttonJustifyEnd->setHeight(70.f);
    buttonJustifySBetween->setWidth(300.f);
    buttonJustifySBetween->setHeight(70.f);

    // manual re-arrange because of resizing
    // TODO: automate re-arrange on resize
    box1->arrangeChildren();
    box7->arrangeChildren();

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}

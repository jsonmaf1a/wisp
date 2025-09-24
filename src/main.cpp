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

    auto sidebarBox = wisp::Box::create() // > 1.f means value in px
                          ->setSize({LayoutConfig::WindowSize.x * 0.3, LayoutConfig::WindowSize.y})
                          ->setDirection(wisp::Flex::Direction::Type::Row)
                          ->setJustification(wisp::Flex::Justification::Type::End);

    auto box1 = wisp::Box::create()->setSize({125, 50});
    auto box2 = wisp::Box::create()->setSize({125, 50});
    auto box3 = wisp::Box::create()->setSize({sidebarBox->getWidth(), 50});
    auto box4 = wisp::Box::create()->setSize({65, 50});
    auto box5 = wisp::Box::create()->setSize({200, 50});

    sidebarBox->addChildren(box1, box2, box3, box4, box5);

    sf::Font font;
    bool _ = font.openFromFile("/home/hapka/dev/chess-cpp/assets/fonts/static/Roboto-Regular.ttf");

    auto buttonStart = std::make_shared<wisp::Button>("Start", font, 16);
    buttonStart->setSize({200.f, 50.f});
    buttonStart->setOnClick([sidebarBox](auto &ctx) {
        sidebarBox->setJustification(wisp::Flex::Justification::Type::Start);
        return wisp::EventResult::Consumed;
    });

    auto buttonCenter = std::make_shared<wisp::Button>("Center", font, 16);
    buttonCenter->setSize({200.f, 50.f});
    buttonCenter->setOnClick([sidebarBox](auto &ctx) {
        sidebarBox->setJustification(wisp::Flex::Justification::Type::Center);
        return wisp::EventResult::Consumed;
    });

    auto buttonEnd = std::make_shared<wisp::Button>("End", font, 16);
    buttonEnd->setSize({200.f, 50.f});
    buttonEnd->setOnClick([sidebarBox](auto &ctx) {
        sidebarBox->setJustification(wisp::Flex::Justification::Type::End);
        return wisp::EventResult::Consumed;
    });

    auto buttonSpaceBetween = std::make_shared<wisp::Button>("SpaceBetween", font, 16);
    buttonSpaceBetween->setSize({200.f, 50.f});
    buttonSpaceBetween->setOnClick([sidebarBox](auto &ctx) {
        sidebarBox->setJustification(wisp::Flex::Justification::Type::SpaceBetween);
        return wisp::EventResult::Consumed;
    });

    auto buttonSpaceAround = std::make_shared<wisp::Button>("SpaceAround", font, 16);
    buttonSpaceAround->setSize({200.f, 50.f});
    buttonSpaceAround->setOnClick([sidebarBox](auto &ctx) {
        sidebarBox->setJustification(wisp::Flex::Justification::Type::SpaceAround);
        return wisp::EventResult::Consumed;
    });

    auto buttonSpaceEvenly = std::make_shared<wisp::Button>("SpaceEvenly", font, 16);
    buttonSpaceEvenly->setSize({200.f, 50.f});
    buttonSpaceEvenly->setOnClick([sidebarBox](auto &ctx) {
        sidebarBox->setJustification(wisp::Flex::Justification::Type::SpaceEvenly);
        return wisp::EventResult::Consumed;
    });

    auto mainBox = wisp::Box::create()
                       ->setSize({LayoutConfig::WindowSize.x * 0.7, LayoutConfig::WindowSize.y})
                       ->setJustification(wisp::Flex::Justification::Type::SpaceBetween)
                       ->setDirection(wisp::Flex::Direction::Type::Column);
    mainBox->addChildren(buttonStart, buttonCenter, buttonEnd, buttonSpaceAround,
                         buttonSpaceBetween, buttonSpaceEvenly);

    ui.addComponents(sidebarBox, mainBox);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}

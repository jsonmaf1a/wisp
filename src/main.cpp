#include "config/LayoutConfig.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <wisp/common/Dimensions.hpp>
#include <wisp/core/Window.hpp>
#include <wisp/core/flex/FlexJustification.hpp>
#include <wisp/ui/Button.hpp>

using namespace wisp;

// /*
int main()
{
    Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto sidebarBox = Box::create()
                          ->setDirection(Flex::Direction::Row)
                          ->setJustification(Flex::Justification::Center)
                          ->setFullHeight()
                          ->setWidth(.3, Size::Unit::Percent);

    auto box1 = Box::create()->setSize({125, 25})->attachTo(sidebarBox);
    auto box2 = Box::create()->setSize({125, 25})->attachTo(sidebarBox);
    auto box3 = Box::create()->setSize({160, 50})->attachTo(sidebarBox);
    auto box4 = Box::create()->setSize({160, 50})->attachTo(sidebarBox);
    auto box5 = Box::create()->setSize({100, 100})->attachTo(sidebarBox);
    auto box6 = Box::create()
                    ->setWidth(1.0f, Size::Unit::Percent)
                    ->setHeight(53, Size::Unit::Pixels)
                    ->attachTo(sidebarBox);
    auto box7 = Box::create()->setSize({.9, .6}, Size::Unit::Percent)->attachTo(sidebarBox);
    auto box8 = Box::create()->setSize({.2, .2}, Size::Unit::Percent)->attachTo(sidebarBox);
    auto box9 = Box::create()->setSize({.2, .2}, Size::Unit::Percent)->attachTo(sidebarBox);
    auto box10 = Box::create()->setSize({.2, .2}, Size::Unit::Percent)->attachTo(sidebarBox);
    auto box11 = Box::create()->setSize({.2, .2}, Size::Unit::Percent)->attachTo(sidebarBox);

    sf::Font font;
    bool _ = font.openFromFile("/home/hapka/dev/chess-cpp/assets/fonts/static/Roboto-Regular.ttf");

    auto mainBox = Box::create()
                       ->setJustification(Flex::Justification::SpaceBetween)
                       ->setDirection(Flex::Direction::Column)
                       ->setFullHeight()
                       ->setWidth(.7f, Size::Unit::Percent);

    auto buttonStart = Button::create("Start", font)
                           ->setOnClick([sidebarBox](auto &ctx) {
                               sidebarBox->setJustification(Flex::Justification::Start);
                               return EventResult::Consumed;
                           })
                           ->setSize({200.f, 60.f})
                           ->attachTo(mainBox);

    auto buttonCenter = Button::create("Center", font)
                            ->setOnClick([sidebarBox](auto &ctx) {
                                sidebarBox->setJustification(Flex::Justification::Center);
                                return EventResult::Consumed;
                            })
                            ->setSize({200.f, 60.f})
                            ->attachTo(mainBox);

    auto buttonEnd = Button::create("End", font)
                         ->setOnClick([sidebarBox](auto &ctx) {
                             sidebarBox->setJustification(Flex::Justification::End);
                             return EventResult::Consumed;
                         })
                         ->setSize({200.f, 60.f})
                         ->attachTo(mainBox);

    auto buttonSpaceBetween =
        Button::create("SpaceBetween", font)
            ->setOnClick([sidebarBox](auto &ctx) {
                sidebarBox->setJustification(Flex::Justification::SpaceBetween);
                return EventResult::Consumed;
            })
            ->setSize({200.f, 60.f})
            ->attachTo(mainBox);

    auto buttonSpaceAround = Button::create("SpaceAround", font)
                                 ->setOnClick([sidebarBox](auto &ctx) {
                                     sidebarBox->setJustification(Flex::Justification::SpaceAround);
                                     return EventResult::Consumed;
                                 })
                                 ->setSize({200.f, 60.f})
                                 ->attachTo(mainBox);

    auto buttonSpaceEvenly = Button::create("SpaceEvenly", font)
                                 ->setOnClick([sidebarBox](auto &ctx) {
                                     sidebarBox->setJustification(Flex::Justification::SpaceEvenly);
                                     return EventResult::Consumed;
                                 })
                                 ->setSize({200.f, 60.f})
                                 ->attachTo(mainBox);

    auto buttonToggleSidebar = Button::create("Toggle sidebar", font)
                                   ->setOnClick([sidebarBox](auto &ctx) {
                                       sidebarBox->setVisible(!sidebarBox->isVisible());
                                       return EventResult::Consumed;
                                   })
                                   ->setSize({200.f, 60.f})
                                   ->attachTo(mainBox);

    ui.addComponents(sidebarBox, mainBox);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}

// */

/*
int main()
{
    Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    sf::Font font;
    bool _ = font.openFromFile("/home/hapka/dev/chess-cpp/assets/fonts/static/Roboto-Regular.ttf");

    auto box1 = Box::create()
                    ->setDirection(Flex::Direction::Row)
                    ->setJustification(Flex::Justification::Center)
                    ->setFullHeight()
                    ->setFullWidth();

    auto box2 =
        Box::create()->setSize({125, 25}, DimensionSize::Unit::Pixels)->attachTo(box1);

    float transitionDurationSecs = 0.5f;
    sf::Vector2f targetPos = {544, 321};
    auto positionTransition = std::make_shared<PropertyTransition<sf::Vector2f>>(
        static_cast<sf::Vector2f>(box2->getBounds().position), static_cast<sf::Vector2f>(targetPos),
        transitionDurationSecs, [box2, targetPos](sf::Vector2f newPosition) {
            box2->setBounds({targetPos, box2->getBounds().size});
        });

    auto buttonToggleSidebar = Button::create("Toggle sidebar", font)
                                   ->setOnClick([box2, positionTransition](auto &ctx) {
                                       TransitionManager::addTransition(positionTransition);
                                       return EventResult::Consumed;
                                   })
                                   ->setSize({200.f, 60.f})
                                   ->attachTo(box1);

    ui.addComponents(box1);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}
*/

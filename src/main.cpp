#include "config/LayoutConfig.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <wisp/core/Window.hpp>

int main()
{
    Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto box1 = std::make_shared<Box>(renderWindow, sf::FloatRect{{0, 0}, {275, 800}});
    auto box2 = std::make_shared<Box>(renderWindow, sf::FloatRect{{0, 0}, {130, 50}});
    auto box3 = std::make_shared<Box>(renderWindow, sf::FloatRect{{0, 0}, {120, 50}});
    auto box4 = std::make_shared<Box>(renderWindow, sf::FloatRect{{0, 0}, {270, 50}});
    auto box5 = std::make_shared<Box>(renderWindow, sf::FloatRect{{0, 0}, {100, 40}});
    auto box6 = std::make_shared<Box>(renderWindow, sf::FloatRect{{0, 0}, {100, 40}});

    box1->addChild(box2);
    box1->addChild(box3);
    box1->addChild(box4);
    box1->addChild(box5);
    box1->addChild(box6);
    ui.addComponent(box1);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}

#include "config/LayoutConfig.hpp"
#include <SFML/Graphics.hpp>
#include <wisp/core/Window.hpp>
#include <wisp/ui/Box.hpp>

int main()
{
    Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto box = std::make_shared<Box>(
        renderWindow,
        sf::FloatRect{{0.f, 0.f},
                      {LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y}},
        sf::FloatRect{
            {0.f, 0.f},
            {LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y}});
    ui.addComponent(box);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}

#include "config/LayoutConfig.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <wisp/core/Window.hpp>

int main()
{
    Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto box1 = std::make_shared<Box>(renderWindow);
    auto box2 = std::make_shared<Box>(renderWindow);

    ui.addComponents(box1, box2);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}

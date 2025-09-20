#include "wisp/core/Window.hpp"
#include "wisp/utils/EventUtils.hpp"
#include <SFML/Window/Cursor.hpp>

Window::Window(uint width, uint height, const std::string &title)
    : ui(dispatcher)
    , cursorManager(window)
{
    window.create(sf::VideoMode({width, height}), title, sf::Style::Close,
                  sf::State::Windowed);
    window.setVerticalSyncEnabled(true);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int x = (desktop.size.x - width) / 2;
    int y = (desktop.size.y - height) / 2;

    window.setPosition(sf::Vector2i(x, y));

    isInitialized = true;
}

Window::~Window()
{
    if(isInitialized)
        window.close();

    isInitialized = false;
}

void Window::update()
{
    window.clear();

    ui.draw(window);

    window.display();
}

void Window::pollEvents()
{
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
            window.close();

        if(const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            if(keyPressed->code == sf::Keyboard::Key::Escape)
                window.close();

        if(EventUtils::isMouseEvent(event.value()))
        {
            dispatcher.dispatch(
                EventContext(event.value(), window, cursorManager));
        }
    }
}

sf::RenderWindow &Window::getRenderWindow() { return window; }
EventDispatcher &Window::getEventDispatcher() { return dispatcher; }
UIManager &Window::getUI() { return ui; }

bool Window::isOpen() const { return window.isOpen(); }

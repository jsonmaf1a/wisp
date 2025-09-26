#include <SFML/Window/Cursor.hpp>
#include <wisp/core/Window.hpp>
#include <wisp/ui/Box.hpp>
#include <wisp/utils/EventUtils.hpp>

namespace wisp
{
    Window::Window(uint width, uint height, const std::string &title)
        : ui(dispatcher)
        , cursorManager(window)
        , title(title)
    {
        window.create(sf::VideoMode({width, height}), title,
                      sf::Style::Close /*  | sf::Style::Resize */, sf::State::Windowed);

        configure();
        createRootBox();

        isInitialized = true;
    }

    Window::~Window()
    {
        if(isInitialized)
            window.close();

        isInitialized = false;
    }

    void Window::configure()
    {
        window.setVerticalSyncEnabled(true);

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        int x = (desktop.size.x - window.getSize().x) / 2;
        int y = (desktop.size.y - window.getSize().y) / 2;
        window.setPosition(sf::Vector2i(x, y));
    }

    void Window::createRootBox()
    {
        auto width = static_cast<float>(window.getSize().x);
        auto height = static_cast<float>(window.getSize().y);

        auto rootBox =
            wisp::Box::create()->setSize({width, height})->setAvailableSpace({width, height});
        // ->setSize({width, height}, DimensionSize::Unit::Pixels)

        ui.setRootBox(rootBox);
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
                dispatcher.dispatch(EventContext(event.value(), window, cursorManager));
            }
        }
    }

    sf::RenderWindow &Window::getRenderWindow() { return window; }

    EventDispatcher &Window::getEventDispatcher() { return dispatcher; }

    UIManager &Window::getUI() { return ui; }

    bool Window::isOpen() const { return window.isOpen(); }
    const std::string &Window::getTitle() const { return title; }
} // namespace wisp

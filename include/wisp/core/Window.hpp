#pragma once

#include "wisp/core/managers/CursorManager.hpp"
#include "wisp/core/managers/EventDispatcher.hpp"
#include "wisp/core/managers/UIManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <string>

class Window
{
  public:
    static constexpr const char *WINDOW_TITLE = "wisp_window";

    Window(uint width, uint height, const std::string &title = WINDOW_TITLE);
    ~Window();

    void update();
    void pollEvents();
    bool isOpen() const;

    sf::RenderWindow &getRenderWindow();
    EventDispatcher &getEventDispatcher();
    UIManager &getUI();

  private:
    sf::RenderWindow window;
    EventDispatcher dispatcher;
    CursorManager cursorManager;
    UIManager ui;

    bool isInitialized = false;
};

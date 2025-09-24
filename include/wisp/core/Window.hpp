#pragma once

#include "../core/managers/CursorManager.hpp"
#include "../core/managers/EventDispatcher.hpp"
#include "../core/managers/UIManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <string>

namespace wisp
{
    class Window
    {
      public:
        Window(uint width, uint height, const std::string &title = WINDOW_DEFAULT_TITLE);
        ~Window();

        void update();
        void pollEvents();
        sf::RenderWindow &getRenderWindow();
        EventDispatcher &getEventDispatcher();
        UIManager &getUI();
        const std::string &getTitle() const;
        bool isOpen() const;

      private:
        bool isInitialized = false;

        const std::string &title;
        sf::RenderWindow window;
        EventDispatcher dispatcher;
        CursorManager cursorManager;
        UIManager ui;

        void configure();
        void createRootBox();

        static constexpr const char *WINDOW_DEFAULT_TITLE = "wisp_window";
    };
} // namespace wisp

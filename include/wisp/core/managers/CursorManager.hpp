#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class CursorManager
{
  public:
    CursorManager(sf::RenderWindow &window);
    ~CursorManager() = default;

    void setHandCursor();
    void resetCursor();

  private:
    sf::RenderWindow &window;
    std::unique_ptr<sf::Cursor> handCursor;
    std::unique_ptr<sf::Cursor> defaultCursor;
};

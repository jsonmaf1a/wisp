#pragma once

#include "wisp/events/Events.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class EventHandler
{
  protected:
    EventHandler() = default;

  public:
    virtual ~EventHandler() = default;

    virtual EventResult handleEvent(const EventContext &eventCtx)
    {
        return EventResult::Ignored;
    };
};

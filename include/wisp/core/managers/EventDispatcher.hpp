#pragma once

#include "../../events/EventHandler.hpp"
#include <memory>
#include <vector>

namespace wisp
{
    class EventDispatcher
    {
      private:
        std::vector<std::weak_ptr<EventHandler>> listeners;

      public:
        void registerListener(std::shared_ptr<EventHandler> listener);
        void unregisterListener(std::shared_ptr<EventHandler> listener);
        void dispatch(const EventContext &eventCtx);
    };
} // namespace wisp

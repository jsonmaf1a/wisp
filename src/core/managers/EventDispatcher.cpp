#include <wisp/core/managers/EventDispatcher.hpp>

void EventDispatcher::registerListener(std::shared_ptr<EventHandler> listener)
{
    listeners.push_back(listener);
}

void EventDispatcher::unregisterListener(std::shared_ptr<EventHandler> listener)
{
    listeners.erase(
        std::remove_if(
            listeners.begin(), listeners.end(),
            [&listener](const std::weak_ptr<EventHandler> &weakListener) {
                auto ptr = weakListener.lock();
                return !ptr || ptr == listener;
            }),
        listeners.end());
}

void EventDispatcher::dispatch(const EventContext &eventCtx)
{
    for(auto it = listeners.rbegin(); it != listeners.rend(); ++it)
    {
        if(auto listener = it->lock())
        {
            if(listener->handleEvent(eventCtx) == EventResult::Consumed)
            {
                break;
            }
        }
    }
}

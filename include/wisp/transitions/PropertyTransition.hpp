#pragma once

#include "wisp/transitions/Transition.hpp"
#include <functional>

template <typename T> class PropertyTransition : public Transition
{
  public:
    PropertyTransition(T start, T end, float duration,
                       std::function<void(T)> applyValue)
        : Transition(duration)
        , start(start)
        , end(end)
        , applyValue(applyValue)
    {}

    void update(float deltaTime) override
    {
        Transition::update(deltaTime);

        float t = elapsedTime / duration;
        T currentValue = interpolate(start, end, t);

        applyValue(currentValue);
    }

  private:
    T start;
    T end;
    std::function<void(T)> applyValue;

    T interpolate(const T &start, const T &end, float t);
};

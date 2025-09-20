#pragma once
#include "wisp/transitions/Transition.hpp"
#include <memory>

namespace TransitionManager
{
    void update(float deltaTime);
    void addTransition(std::shared_ptr<Transition> transition);

}; // namespace TransitionManager

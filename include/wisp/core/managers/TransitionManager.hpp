#pragma once
#include "../../transitions/Transition.hpp"
#include <memory>

namespace wisp::TransitionManager
{
    void update(float deltaTime);
    void addTransition(std::shared_ptr<Transition> transition);

}; // namespace wisp::TransitionManager

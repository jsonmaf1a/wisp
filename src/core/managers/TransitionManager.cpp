#include <vector>
#include <wisp/core/managers/TransitionManager.hpp>

namespace
{
    std::vector<std::shared_ptr<wisp::Transition>> transitions;
}

namespace wisp::TransitionManager
{

    void update(float deltaTime)
    {
        for(auto it = transitions.begin(); it != transitions.end();)
        {
            (*it)->update(deltaTime);

            if((*it)->isFinished())
            {
                it = transitions.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void addTransition(std::shared_ptr<Transition> transition)
    {
        transitions.push_back(transition);
    }
} // namespace wisp::TransitionManager

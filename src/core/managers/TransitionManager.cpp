#include <vector>
#include <wisp/core/managers/TransitionManager.hpp>

namespace
{
    static std::vector<std::shared_ptr<Transition>> transitions;
}

namespace TransitionManager
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
} // namespace TransitionManager

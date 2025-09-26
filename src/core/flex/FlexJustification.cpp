#include <wisp/core/flex/FlexJustification.hpp>

namespace wisp::Flex
{
    void FlexEnd::apply(FlexLine &line, bool isRow)
    {
        const float offset = line.remainingSpace;
        for(auto &child : line.items)
        {
            auto bounds = child->getBounds();
            if(isRow)
                bounds.position.x += offset;
            else
                bounds.position.y += offset;
            child->setBounds(bounds);
        }
    }

    void Center::apply(FlexLine &line, bool isRow)
    {
        const float offset = line.remainingSpace / 2.0f;
        for(auto &child : line.items)
        {
            auto bounds = child->getBounds();
            if(isRow)
                bounds.position.x += offset;
            else
                bounds.position.y += offset;
            child->setBounds(bounds);
        }
    }

    void SpaceBetween::apply(FlexLine &line, bool isRow)
    {
        if(line.items.size() <= 1)
            return;

        const float spaceBetween = line.remainingSpace / (line.items.size() - 1);

        for(size_t i = 1; i < line.items.size(); ++i)
        {
            const float additionalOffset = spaceBetween * i;
            auto bounds = line.items[i]->getBounds();
            if(isRow)
                bounds.position.x += additionalOffset;
            else
                bounds.position.y += additionalOffset;
            line.items[i]->setBounds(bounds);
        }
    }

    void SpaceAround::apply(FlexLine &line, bool isRow)
    {
        const float spacePerItem = line.remainingSpace / line.items.size();
        const float halfSpace = spacePerItem / 2.0f;

        for(size_t i = 0; i < line.items.size(); ++i)
        {
            const float offset = halfSpace + (spacePerItem * i);
            auto bounds = line.items[i]->getBounds();
            if(isRow)
                bounds.position.x += offset;
            else
                bounds.position.y += offset;
            line.items[i]->setBounds(bounds);
        }
    }

    void SpaceEvenly::apply(FlexLine &line, bool isRow)
    {
        const float spaceUnit = line.remainingSpace / (line.items.size() + 1);

        for(size_t i = 0; i < line.items.size(); ++i)
        {
            const float offset = spaceUnit * (i + 1);
            auto bounds = line.items[i]->getBounds();
            if(isRow)
                bounds.position.x += offset;
            else
                bounds.position.y += offset;
            line.items[i]->setBounds(bounds);
        }
    }

    std::unique_ptr<Strategy> createJustificationStrategy(Flex::Justification type)
    {
        switch(type)
        {
            case Flex::Justification::Start:
                return std::make_unique<FlexStart>();
            case Flex::Justification::End:
                return std::make_unique<FlexEnd>();
            case Flex::Justification::Center:
                return std::make_unique<Center>();
            case Flex::Justification::SpaceBetween:
                return std::make_unique<SpaceBetween>();
            case Flex::Justification::SpaceAround:
                return std::make_unique<SpaceAround>();
            case Flex::Justification::SpaceEvenly:
                return std::make_unique<SpaceEvenly>();
        }
        return std::make_unique<FlexStart>();
    }
} // namespace wisp::Flex

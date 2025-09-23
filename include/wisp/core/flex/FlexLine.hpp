#pragma once

#include "wisp/core/Component.hpp"
#include <memory>
#include <vector>

namespace Flex
{
    struct FlexLine
    {
        std::vector<std::shared_ptr<Component>> items;
        float totalMainSize = 0.f;
        float maxCrossSize = 0.f;
        float remainingSpace = 0.f;
    };
} // namespace Flex

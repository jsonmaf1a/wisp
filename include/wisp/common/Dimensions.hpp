#pragma once

namespace wisp
{
    struct Size
    {
        enum class Unit
        {
            Pixels,
            Percent
        };

        float value;
        Unit unit;

        float resolve(float parentSize) const
        {
            return (unit == Unit::Pixels) ? value : parentSize * value;
        }
    };

    struct SizeSpec
    {
        Size width;
        Size height;
    };
} // namespace wisp

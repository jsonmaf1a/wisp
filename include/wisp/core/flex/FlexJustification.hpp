#pragma once

#include "FlexLine.hpp"

namespace wisp::Flex::Justification
{
    enum class Type
    {
        Start,
        Center,
        End,
        SpaceBetween,
        SpaceAround,
        SpaceEvenly,
    };

    class Strategy
    {
      public:
        virtual ~Strategy() = default;
        virtual void apply(FlexLine &line, bool isRow) = 0;
    };

    class FlexStart : public Strategy
    {
        void apply(FlexLine &line, bool isRow) override final
        {
            // No positioning needed
        }
    };

    class FlexEnd : public Strategy
    {
        void apply(FlexLine &line, bool isRow) override final;
    };

    class Center : public Strategy
    {
        void apply(FlexLine &line, bool isRow) override final;
    };

    class SpaceBetween : public Strategy
    {
        void apply(FlexLine &line, bool isRow) override final;
    };

    class SpaceAround : public Strategy
    {
        void apply(FlexLine &line, bool isRow) override final;
    };

    class SpaceEvenly : public Strategy
    {
        void apply(FlexLine &line, bool isRow) override final;
    };

    std::unique_ptr<Strategy> createStrategy(Type type);
} // namespace wisp::Flex::Justification

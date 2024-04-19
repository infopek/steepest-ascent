#pragma once

namespace core
{
    struct Interval
    {
        float min{};
        float max{};
    };

    struct SearchSpace
    {
        Interval x{};
        Interval y{};
    };
}
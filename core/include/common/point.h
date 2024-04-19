#pragma once

namespace core
{
    struct Point
    {
        float x;
        float y;

        bool operator==(const Point& other) const
        {
            return x == other.x
                && y == other.y;
        }
    };
}

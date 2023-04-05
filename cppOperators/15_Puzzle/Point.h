#ifndef POINT_H
#define POINT_H

#include "Direction.h"

struct Point 
{
    int x{};
    int y{};

    friend bool operator==(const Point& p1, const Point& p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }

    friend bool operator!=(const Point& p1, const Point& p2)
    {
        return !(p1 == p2);
    }

    Point getAdjacentPoint(Direction dir) const
    {
        switch (dir.getDirection())
        {
        case Direction::up: return Point { x, y - 1 }; 
        case Direction::left : return Point { x - 1, y};
        case Direction::down : return Point { x, y + 1};
        case Direction::right: return Point { x + 1, y };
        }

        return *this;
    }
};

#endif

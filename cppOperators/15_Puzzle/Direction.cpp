#include "Direction.h"
#include "Random_MT.h"
#include <cassert>
#include <iostream>

Direction Direction::operator-() const
{
    switch (direction)
    {
        case up:        return down;
        case down:      return up;
        case left:      return right;
        case right:     return left;
    }

    assert(0 && "Unsupported direction passed");
    return Direction{ up };
}

std::ostream& operator<<(std::ostream& out, const Direction& d1)
{
    switch (d1.direction)
    {
        case Direction::up:     return (out << "up");
        case Direction::down:   return (out << "down");
        case Direction::left:   return (out << "left");
        case Direction::right:  return (out << "right");

        default:                return (out << "unknown direction");
    }
}

Direction Direction::getRandomDirection()
{
    Type random{ static_cast<Type>(RandomMT::getRandomInt(0, max_directions - 1)) };
    return Direction{ random };
}

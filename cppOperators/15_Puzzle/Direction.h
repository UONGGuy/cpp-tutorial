#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>

class Direction 
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,

        max_directions,
    };
    
    // Default constructor
    Direction() = default;
    Direction(Type type) : direction{ type }
    {}

    // Direction getter
    Type getDirection() const { return direction; }

    // Overloaded functions
    Direction operator-() const;
    friend std::ostream& operator<<(std::ostream& out, const Direction& d1);

    // Random Direction getter
    static Direction getRandomDirection();

private:
    Type direction{};

};


#endif

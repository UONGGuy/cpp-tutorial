#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <cassert>

class Tile 
{
private:
    int number{ 0 };

public:
    // Constructors
    Tile() = default;
    explicit Tile(int n) : number{ n }
    {
        assert(n >= 0 && n < 16 && "Tile number out-of-bounds.");
    }

    int getNum() const { return number; }
    bool isEmpty() const { return number == 0; }
};

inline std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    if (tile.isEmpty())
        out << "    ";
    else
    {
        if (tile.getNum() < 10)
            out << ' ';
        out << ' ';
        out << tile.getNum();
        out << ' ';
    }
    return out;
}

inline bool operator==(const Tile& t1, const Tile& t2)
{
    return t1.getNum() == t2.getNum();
}

inline bool operator!=(const Tile& t1, const Tile& t2)
{
    return !(t1 == t2);
}
#endif

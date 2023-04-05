#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include "Tile.h"

constexpr int g_consoleLines{ 25 };

class Board 
{
private:
    static constexpr int grid_size{ 4 };
    Tile boardState[grid_size][grid_size]{};
    static constexpr int rand_moves{ 1000 };
    
public:
    Board();

    static void printEmptyLines(int count);

    friend std::ostream& operator<<(std::ostream& out, const Board& b1);

    friend bool operator==(const Board& b1, const Board& b2);

    Point getEmptyTileLoc() const;

    static bool isValidSwap(Point pt);

    void swapTiles(Point p1, Point p2);

    bool swapExecuted(Direction dir);

    void randomise();
};

#endif

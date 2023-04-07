#include "Board.h"
#include "UserInput.h"
#include <algorithm>
#include <iostream>
#include <string>

Board::Board()
{
    for (int i{ 0 }; i < grid_size * grid_size; ++i)
    {
        int n = i + 1;
        int y = i / grid_size;
        int x = i % grid_size;
        if (n < 16)
            boardState[y][x] = Tile{ n };
        else
            boardState[y][x] = Tile{ 0 };
    }
}

void Board::printEmptyLines(int count)
{
    for (int line{ 0 }; line < g_consoleLines; ++line)
        std::cout << '\n';
}

std::ostream& operator<<(std::ostream& out, const Board& b1)
{
    b1.printEmptyLines(g_consoleLines);

    for (int y{ 0 }; y < b1.grid_size; ++y)
    {
        for (int x{ 0 }; x < b1.grid_size; ++x)
        {
            out << b1.boardState[y][x];
        }
        out << '\n';
    }
    return out;
}

bool operator==(const Board& b1, const Board& b2)
{
    for (int y{ 0 }; y < b1.grid_size; ++y)
    {
        for (int x{ 0 }; x < b1.grid_size; ++x)
        {
            if (b1.boardState[y][x] != b2.boardState[y][x])
                return false;
        }
    }
    return true;
}

Point Board::getEmptyTileLoc() const
{
    for (int y{ 0 }; y < grid_size; ++y)
    {
        for (int x{ 0 }; x < grid_size; ++x)
        {
            if (boardState[y][x].isEmpty())
                return { x, y };
        }
    }
    
    assert(0 && "No empty tile in board.");
    return { -1, -1 };
}

bool Board::isValidSwap(Point pt)
{
    return (pt.x >= 0 && pt.x < grid_size && pt.y >= 0 && pt.y < grid_size);
}

void Board::swapTiles(Point p1, Point p2)
{
    std::swap(boardState[p1.y][p1.x], boardState[p2.y][p2.x]);
}

bool Board::swapExecuted(Direction dir)
{
    Point emptyTile{ getEmptyTileLoc() };
    Point swapTileTo{ emptyTile.getAdjacentPoint(dir) };

    if (isValidSwap(swapTileTo))
    {
        swapTiles(emptyTile, swapTileTo);
        return true;
    }
    return false;
}

void Board::randomise()
{
    for (int count{ 0 }; count < rand_moves; ++count)
    {
        Direction dir_rand{};
        do
        {
            dir_rand = dir_rand.getRandomDirection();
        }
        while(!swapExecuted(dir_rand));
    }
}

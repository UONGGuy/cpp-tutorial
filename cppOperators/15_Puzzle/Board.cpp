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
        int col = i / grid_size;
        int row = i % grid_size;
        if (n < 16)
            boardState[col][row] = Tile{ n };
        else
            boardState[col][row] = Tile{ 0 };
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

    for (int col{ 0 }; col < b1.grid_size; ++col)
    {
        for (int row{ 0 }; row < b1.grid_size; ++row)
        {
            out << b1.boardState[col][row];
        }
        out << '\n';
    }
    return out;
}

bool operator==(const Board& b1, const Board& b2)
{
    for (int col{ 0 }; col < b1.grid_size; ++col)
    {
        for (int row{ 0 }; row < b1.grid_size; ++row)
        {
            if (b1.boardState[col][row] != b2.boardState[col][row])
                return false;
        }
    }
    return true;
}

Point Board::getEmptyTileLoc() const
{
    for (int col{ 0 }; col < grid_size; ++col)
    {
        for (int row{ 0 }; row < grid_size; ++row)
        {
            if (boardState[col][row].isEmpty())
                return { row, col };
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

#include "Board.h"
#include "Direction.h"
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>

namespace UserInput
{
    bool isValidInput(char in)
    {
        return in == 'w'
            || in == 'a'
            || in == 's'
            || in == 'd'
            || in == 'q';
    }

    void clearBuffer()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getChar()
    {
        char command{};
        std::cin >> command;
        clearBuffer();
        return command;
    }

    char getCommandFromUser()
    {
        char command{};
        while (!isValidInput(command))
            command = getChar();

        return command;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 'a': return Direction{ Direction::left };
        case 's': return Direction{ Direction::down };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction passed.");
        return Direction{ Direction::up };
    }
}

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
        

int main()
{
    Board board{};
    std::cout << board;

    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << "\n\n";

    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::up) == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::down) == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::left) == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::right) == Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1, } != Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1, } != Point{ 1, 2 }) << '\n';
    std::cout << !(Point{ 1, 1, } != Point{ 1, 1 }) << '\n';

    while (true)
    {
        char command{ UserInput::getCommandFromUser() };
        std::cout << "Valid command: " << command << '\n';

        if (command == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            break;
        }

        Direction dir{ UserInput::charToDirection(command) };
        std::cout << "You entered direction: " << dir << '\n';
    }

    return 0;
}

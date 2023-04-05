#include "Board.h"
#include "UserInput.h"
#include <iostream>

int main()
{
    Board board{};
    board.randomise();
    Board completeBoard{};
    std::cout << board;

    while (true)
    {
        if (board == completeBoard)
        {
            std::cout << "You win!\n";
            return 0;
        }

        std::cout << "Enter a command: ";
        char command{ UserInput::getCommandFromUser() };

        if (command == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        Direction dir{ UserInput::charToDirection(command) };
        
        bool userMove{ board.swapExecuted(dir) };
        if (userMove)
            std::cout << board;
    }

    return 0;
}

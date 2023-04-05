#include "UserInput.h"

bool UserInput::isValidInput(char in)
{
    return in == 'w'
        || in == 'a'
        || in == 's'
        || in == 'd'
        || in == 'q';
}

void UserInput::clearBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char UserInput::getChar()
{
    char command{};
    std::cin >> command;
    clearBuffer();
    return command;
}

char UserInput::getCommandFromUser()
{
    char command{};
    while (!isValidInput(command))
        command = getChar();

    return command;
}

Direction UserInput::charToDirection(char ch)
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

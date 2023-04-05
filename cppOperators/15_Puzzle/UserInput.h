#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "Direction.h"
#include <cassert>
#include <iostream>
#include <limits>

namespace UserInput
{
    bool isValidInput(char in);

    void clearBuffer();

    char getChar();

    char getCommandFromUser();

    Direction charToDirection(char ch);
}

#endif

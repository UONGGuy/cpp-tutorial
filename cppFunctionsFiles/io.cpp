/*  File containing functions for main2.cpp */

#include "io.h"
#include <iostream>

int readNumber()
{
    int x {};
    std::cout << "Choose integer: ";
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The sum of the above integers is " << x << std::endl;
}

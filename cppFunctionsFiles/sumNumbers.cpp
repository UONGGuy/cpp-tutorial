/*  Program to print the sum of two input integers.
    
    INPUT: int x, y;

    OUTPUT: int (x + y)

    Uses function from getInt.cpp

*/

#include <iostream>

// Function declaration
int getInteger();

int main()
{
    int x{ getInteger() };
    int y{ getInteger() };

    std::cout << x << " + " << y << " is " << x + y << '\n';
    return 0;
}

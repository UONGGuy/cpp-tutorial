/*  Program to return double the value of input integer using functions.

    INPUT: int x

    OUTPUT: int (2 * x)

*/

#include <iostream>

// Function to return double the input integer
int doubleInput(int x)
{
    return 2 * x;
}

int main()
{
    // Input integer
    int x{};

    std::cout << "Choose integer to double: ";
    std::cin >> x;
    std::cout << "Double of " << x << " is " << doubleInput(x) << 
    std::endl;

    return 0;
}

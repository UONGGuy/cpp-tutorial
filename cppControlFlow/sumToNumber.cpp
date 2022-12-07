/*  sumToNumber.cpp

    Program to output sum of all integers from 1 to user-input.

*/

#include <iostream>

int sumTo(int endValue)
{
    int totalSum { 0 };
    
    for (int count { 1 }; count <= endValue; ++count)
    {
        totalSum += count;
    }

    return totalSum;
}

int main()
{
    int endValue {};
    std::cout << "Choose an integer: ";
    std::cin >> endValue;

    int totalSum { sumTo(endValue) };

    std::cout << "The sum of all integers up to " << endValue << " is " << totalSum << "\n";

    return 0;
}

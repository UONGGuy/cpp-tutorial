/*  digitAdder.cpp

    Program to find the sum of the digits of an integer.

*/

#include <iostream>

int digitAdder(int number)
{
    if (number / 10 == 0)
        return number;
    else
        return (number % 10) + digitAdder(number / 10);
}

int getInteger()
{
    while(true)
    {
        std::cout << "Enter an integer: ";
        int value{};
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return value;
    }
}

int main()
{
    int value{ getInteger() };

    std::cout << "The sum of its digits is " << digitAdder(value) << '\n';

    return 0;
}

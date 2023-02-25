/*  binaryRepresent2.cpp

    Program to print the binary representation of an integer.
    Includes case for 0 or negative number.

    Turn negative int to a positive one by converting to unsigned int.
    Then apply usual bit representation.

*/

#include <iostream>

void printBinary(unsigned int n)
{
    if (n > 1)
        printBinary(n / 2);
    std::cout << n % 2;
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

    printBinary(static_cast<unsigned int>(value));
    std::cout << '\n';

    return 0;
}

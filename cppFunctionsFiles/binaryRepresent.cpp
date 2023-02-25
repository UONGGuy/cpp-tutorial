/*  binaryRepresent.cpp

    Program to print the binary representation of an integer.

*/

#include <iostream>

int decToBin(int dec_value)
{
    if (dec_value == 0)
        return 0;
    if (dec_value == 1)
        return 1;
    else
        return dec_value % 2 + 10 * decToBin(dec_value / 2);
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

    std::cout << "In binary: " << decToBin(value) << '\n';

    return 0;
}

/*  asciiPrint.cpp

    Program to print the letters a - z along with their ASCII codes.

*/

#include <iostream>

int main()
{
    char letter {'a'};

    while (letter <= 'z')
    {
        std::cout << letter << "\t" << static_cast<int>(letter) << "\n";
        ++letter;
    }

    return 0;
}

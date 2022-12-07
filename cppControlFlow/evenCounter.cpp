/*  evenCounter.cpp

    Program to print every even number from 0 - 20.

*/

#include <iostream>

int main()
{
    for (int i { 0 }; i <= 20; ++i)
    {
        if (i % 2 == 0)
        {
            std::cout << i << ' ';
        }
    }

    std::cout << std::endl;

    return 0;
}

/*  upperTriangular.cpp

    Program to print the following:

    5 4 3 2 1
    4 3 2 1
    3 2 1
    2 1
    1

*/

#include <iostream>

int main()
{
    int count { 0 };

    while (count < 5)
    {
    int x { 5 - count };

    while (x > 0)
    {
        std::cout << x << " ";
        --x;
    }

    std::cout << '\n';

    ++count;
    }

    return 0;
}

/*  multiplier.cpp

    Function to multiply a value of any type with an integer, 
    returning the same type as the first parameter.

*/
#include <iostream>

template <typename T>
T mult(T x, int y)
{
    return x * y;
}

int main()
{
    std::cout << mult(2, 3) << '\n';
    std::cout << mult(1.2, 3) << '\n';

    return 0;
}


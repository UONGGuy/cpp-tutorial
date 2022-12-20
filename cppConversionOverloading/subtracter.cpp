/*  subtracter.cpp

    Program to subtract two values of different types.

*/

#include <iostream>

/* For C++20 and higher

auto sub(auto x, auto y)
{
    return x - y;
}
*/

template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

int main()
{
    std::cout << sub(3, 2) << '\n';
    std::cout << sub(3.5, 2) << '\n';
    std::cout << sub(4, 1.5) << '\n';

    return 0;
}

/*  Triad.cpp

    Program to use CTAD to deduce template arguments.

*/

#include <iostream>

template <typename T>
struct Triad
{
    T x{};
    T y{};
    T z{}; 
};

// deduction guide
template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(const Triad<T>& t)
{
    std::cout << "[" << t.x << ", " << t.y << ", " << t.z << "]";
}

int main()
{
    Triad t1{ 1, 2, 3 };
    print(t1);

    Triad t2{ 1.2, 3.4, 5.6 };
    print(t2);

    return 0;
}

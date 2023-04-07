/*  intPair.cpp

    Program with a class that holds two integers.

    - Two int member variables
    - Member function set() to assign values to ints
    - Member value print() to print values of variables
*/

#include <iostream>

class IntPair
{
public:
    int m_first{};
    int m_second{};

    void set(int x, int y)
    {
        m_first = x;
        m_second = y;
    }

    void print()
    {
        std::cout << "Pair(" << m_first << ", " << m_second << ")\n";
    }
};

int main()
{
    IntPair p1;
    p1.set(1, 1);
    
    IntPair p2{ 2, 2 };

    p1.print();
    p2.print();

    return 0;
}

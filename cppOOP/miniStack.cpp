/*  miniStack.cpp

    Program containing a class to simulate a stack.

*/

#include <iostream>
#include <array>
#include <cassert>

class Stack
{
    using S_array = std::array<int, 10>;
    using S_index = S_array::size_type;

    S_array m_array{}; // holder array
    S_index m_next{ 0 }; // next free index

public:

    void reset()
    {
        m_next = { 0 }; // reset stack size to 0
    }

    bool push(int element)
    {
        if (m_next == m_array.size())
        {
            return false;
        }
        else
        {
            m_array[m_next] = element;
            ++m_next;
            return true;
        }
    }

    int pop()
    {
        assert(m_next > 0 && "Empty stack size 0\n");
        
        return m_array[--m_next];
    }

    void print()
    {
        std::cout << "(";

        for (int i{ 0 }; i < m_next; ++i)
        {
            std::cout << ' ' << m_array[i];
        }

        std::cout << " )\n";
    }
};

int main()
{
    Stack stack;
    stack.print();

    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.print();

    stack.pop();
    stack.print();

    stack.reset();
    stack.print();

    return 0;
}

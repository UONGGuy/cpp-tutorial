/*  Average.cpp
 *
 *  Program to keep track of the average of all integers passed to it.
 *
 */

#include <iostream>
#include <cstdint>
#include <cassert>

class Average
{
private:
    std::int32_t m_cumSum{ 0 };
    std::int8_t m_nValues{ 0 };

public:
    
    Average& operator+=(int value)
    {
        m_cumSum += value;
        ++m_nValues;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Average& avg)
    {
        assert(avg.m_nValues != 0);
        out << static_cast<double>(avg.m_cumSum) / static_cast<double>(avg.m_nValues);
        return out;
    }
};

int main()
{
    Average avg{};

    avg += 4;
    std::cout << avg << '\n';

    avg += 8;
    std::cout << avg << '\n';

    avg += 24;
    std::cout << avg << '\n';

    avg += -10;
    std::cout << avg << '\n';

    (avg += 6) += 10;
    std::cout << avg << '\n';

    Average copy{ avg };
    std::cout << copy << '\n';

    return 0;
}

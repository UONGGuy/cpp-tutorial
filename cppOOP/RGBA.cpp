/*  RGBA.cpp

    Program containing a class with 4 std::uint8_t members: m_red, 
    m_green, m_blue, m_alpha.

    Allows user to initialise values and print member variable values.
*/

#include <iostream>
#include <cstdint> // for std::uint8_t

class RGBA
{
private:
    using CValue = std::uint8_t;
    CValue m_red{};
    CValue m_green{};
    CValue m_blue{};
    CValue m_alpha{};

public:
    RGBA(CValue red=0, CValue green=0, CValue blue=0, CValue alpha=0)
        : m_red{ red }
        , m_green{ green }
        , m_blue{ blue }
        , m_alpha{ alpha }
    {
    }

    void print()
    {
        std::cout << "r=" << static_cast<int>(m_red) << ' ';
        std::cout << "g=" << static_cast<int>(m_green) << ' ';
        std::cout << "b=" << static_cast<int>(m_blue) << ' ';
        std::cout << "a=" << static_cast<int>(m_alpha) << '\n';
    }
};

int main()
{
    RGBA teal{ 0, 127, 127 };
    teal.print();

    return 0;
}

/*  FixedPoint2.cpp
 *
 *  Program to implement a class to hold a value to 2 decimal points.
 *  Range is -32768.99 to 32767.99.
 *  Use 16-bit signed int for integer part, 8-bit signed int for decimal part.
 *
 */

#include <ios>
#include <iostream>
#include <cstdint>
#include <cmath>

class FixedPoint2
{
private:
    std::int16_t m_integer{ 0 };
    std::int8_t m_decimal{ 0 };

public:
    // Default constructor
    FixedPoint2(std::int16_t integer=0, std::int8_t decimal=0)
        : m_integer{ integer }, m_decimal{ decimal }
    {
        if (m_integer < 0 || m_decimal < 0)
        {
            if (m_integer > 0)
                m_integer = -m_integer;
            if (m_decimal > 0)
                m_decimal = -m_decimal;
        }
    }

    // Constructor for double
    FixedPoint2(double value=0.0)
    {
        m_integer = static_cast<std::int16_t>(std::trunc(value));
        m_decimal =static_cast<std::int8_t>(std::round(value * 100) - (m_integer * 100)); 
    }

    // Overload conversion FixedPoint2 -> double
    operator double() const
    {
        return m_integer + (static_cast<double>(m_decimal) / 100);
    }

    // Overload operators
    friend bool operator==(const FixedPoint2& x, const FixedPoint2& y);
    FixedPoint2 operator-();
    FixedPoint2 operator+();

};

std::ostream& operator<<(std::ostream& out, const FixedPoint2& value)
    {
        out << static_cast<double>(value);
        return out;
    }

std::istream& operator>>(std::istream& in, FixedPoint2& value)
{
    double d{};
    in >> d;
    value = FixedPoint2{ d };
    return in;
}

FixedPoint2 operator+(const FixedPoint2& x, const FixedPoint2& y)
{
    return { static_cast<double>(x) + static_cast<double>(y) };
}

bool operator==(const FixedPoint2& x, const FixedPoint2& y)
    {
        return (x.m_integer == y.m_integer && x.m_decimal == y.m_decimal);
    }

FixedPoint2 FixedPoint2::operator-()
    {
        return { static_cast<std::int16_t>(-m_integer), static_cast<std::int8_t>(-m_decimal) };
    }

FixedPoint2 FixedPoint2::operator+()
    {
        return { static_cast<std::int16_t>(m_integer), static_cast<std::int8_t>(m_decimal) };
    }

void testAddition()
{
    std::cout << std::boolalpha;
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n';
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n';
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n';
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n';
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n';
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n';
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n';
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n';
}

int main()
{
    FixedPoint2 a{ 34, 56 };
    std::cout << a << '\n';

    FixedPoint2 b{ -2, 8 };
    std::cout << b << '\n';

    FixedPoint2 c{ 2, -8 };
    std::cout << c << '\n';

    FixedPoint2 d{ -2, -8 };
    std::cout << d << '\n';

    FixedPoint2 e{ 0, -5 };
    std::cout << e << '\n';

    std::cout << static_cast<double>(e) << '\n';

    // Directly representable as double
    FixedPoint2 f{ 0.01 };
    std::cout << f << '\n';

    FixedPoint2 g{ -0.01 };
    std::cout << g << '\n';

    // Rounding error
    FixedPoint2 h{ 5.01 }; // stored as 5.009999...
    std::cout << h << '\n';

    FixedPoint2 i{ -5.01 }; // stored as -5.009999...
    std::cout << i << '\n';

    FixedPoint2 j{ 106.9978 };
    std::cout << j << '\n';

    FixedPoint2 k{ 1.9 };
    std::cout << k << '\n';

    testAddition();

    FixedPoint2 l{ -0.48 };
    std::cout << l << '\n';

    std::cout << -l << '\n';

    std::cout << "Enter a number: ";
    std::cin >> l;

    std::cout << "You entered: " << l << '\n';

    return 0;
}

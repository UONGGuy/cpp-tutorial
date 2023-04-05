/*  Fraction.cpp
 *
 *  Program to practice overloading operators for a function describing
 *  a f1tion.
 *
 */

#include <ios>
#include <iostream>
#include <numeric>
#include <limits>
#include <cassert>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        assert(m_denominator != 0 && "Divide by zero");
        reduce();
    }

    void print() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }

    void reduce()
    {
        int gcd{ std::gcd(m_numerator, m_denominator) };
        if (gcd)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }

    // Overloaded operators
    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f1, int value);
    friend Fraction operator*(int value, const Fraction& f1);
    friend std::istream& operator>>(std::istream& in, Fraction& f1);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    friend bool operator==(const Fraction& f1, const Fraction& f2);
    friend bool operator!=(const Fraction& f1, const Fraction& f2);
    friend bool operator<(const Fraction& f1, const Fraction& f2);
    friend bool operator>(const Fraction& f1, const Fraction& f2);
    friend bool operator<=(const Fraction& f1, const Fraction& f2);
    friend bool operator>=(const Fraction& f1, const Fraction& f2);
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    return { f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator};
}

Fraction operator*(const Fraction& f1, int value)
{
    return { f1.m_numerator * value, f1.m_denominator };
}

Fraction operator*(int value, const Fraction& f1)
{
    return f1 * value;
}

std::istream& operator>>(std::istream& in, Fraction& f1)
{
    in >> f1.m_numerator;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    in >> f1.m_denominator;
    f1.reduce(); // need to re-reduce after overwriting inputs

    return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '/' << f1.m_denominator;

    return out;
}

bool operator==(const Fraction& f1, const Fraction& f2)
{
    return (f1.m_numerator == f2.m_numerator && f1.m_denominator == f2.m_denominator);
}

bool operator!=(const Fraction& f1, const Fraction& f2)
{
    return !(operator==(f1, f2));
}

bool operator<(const Fraction& f1, const Fraction& f2)
{
    return (f1.m_numerator * f2.m_denominator < f2.m_numerator * f1.m_denominator);
}

bool operator>(const Fraction& f1, const Fraction& f2)
{
    return !(operator<(f1, f2));
}

bool operator<=(const Fraction& f1, const Fraction& f2)
{
    return !(operator>(f1, f2));
}

bool operator>=(const Fraction& f1, const Fraction& f2)
{
    return !(operator<(f1, f2));
}

int main()
{
//    Fraction f1{ 2, 5 };
//    f1.print();
//
//    Fraction f2{ 3, 8 };
//    f2.print();
//
//    Fraction f3{ f1 * f2 };
//    f3.print();
//
//    Fraction f4{ f1 * 2 };
//    f4.print();
//    
//    Fraction f5{ 2 * f2 };
//    f5.print();
//
//    Fraction f6{ Fraction{ 1, 2 } * Fraction{ 2, 3 } * Fraction{ 3, 4 } };
//    f6.print();

//    Fraction f1;
//    std::cout << "Enter fraction 1: ";
//    std::cin >> f1;
//
//    Fraction f2;
//    std::cout << "Enter fraction 2: ";
//    std::cin >> f2;
//
//    std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n';

    Fraction f1{ 3, 2 };
    Fraction f2{ 5, 8 };

    std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
    std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
    std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
    std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
    std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
    std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';

    return 0;
}

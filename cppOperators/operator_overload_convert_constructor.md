# Converting constructors

By default, C++ treats any constructors as implicit conversion operators.

```cpp
#include <cassert>
#include <iostream>

class Fraction
{
private:
    int m_numerator;
    int m_denominator;

public:
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        assert(denominator != 0 && "Denominator = 0.";
    }

    Fraction(const Fraction& copy)
        : m_numerator{ copy.m_numerator }
        , m_denominator{ copy.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    int getNumerator() { return m_numerator; }
    void setNumerator(int numerator) { m_numerator = numerator; }
};

void printFraction(const Fraction& f1)
{
    std::cout << f;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '\' << f2.m_denominator;
    return out;
}

int main()
{
    printFraction(6);

    return 0;
}
```

The `Fraction` class has a constructor that is willing to take a single integer and so the compiler implicitly converts the integral literal into a Fraction object.

This implicit conversion works for both direct and copy initialisation with constructors eligible for such use called converting (or conversion) constructors.

## The explicit keyword

Implicit conversions can be undesirable or lead to unexpected behaviours.
For example, problems can arise trying to copy initialise (`=`) a class with a single `char` if a constructor with argument `int`.
Because `char`s are considered part of the integer family, the compiler implicitly converts the `char` input using the `int` constructor.

Prefacing a constructor or member function with the `explicit` keyword addresses this issue by preventing its usage in any implicit conversions or copy initialisation.

Explicit conversions (i.e. via casting with `static_cast`) are still valid.
Direct and uniform initialisation will also implicitly convert parameters to match.

## The delete keyword

If we want to completely disallow a conversion (implicit or explicit), we can do this partially by adding a constructor taking parameters we want to avoid converting to and make this private.

```cpp
#include <string>

class MyString
{
private:
    std::string m_string;

    MyString(char) // objects type MyString(char) cannot be construced outside the class
    {}

public:
    explicit MyString(int x) // explicit keyword makes constructor ineligible for implicit conversions
    {
        m_string.resize(x);
    }
};
```

The private constructor can still be used from within the class.

A better solution is to set the constructor of our disallowed type equal to `delete`

```cpp
MyString(char) = delete; // any use of constructor -> error
```

When a function has been deleted, any use of the function is considered a compile error.

The copy constructor and overloaded operators can also be deleted to prevent them being used.

# Operator overloading with friend functions

Consider the following example class:

```cpp
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } {}

    int getCents() const { return m_cents; }
};
```

We can overload the plus operator `+` to add two `Cents` objects together using friend functions.
To do this, we can declare a function named `operator+` then define it as a friend of the `Cents` class, allowing it to access its private members.

```cpp
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } {}

    // add Cents + Cents using friend function
    friend Cents operator+(const Cents& c1, const Cents& c2);

    int getCents() const { return m_cents; }
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } {}

    // add Cents + Cents using friend function
    friend Cents operator+(const Cents& c1, const Cents& c2);

    int getCents() const { return m_cents; }
};

// This function is NOT a member function
Cents operator+(const Cents& c1, const Cents& c2)
{
    return c1.m_cents + c2.m_cents;
}

int main()
{
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents centsSum{ cents1 + cents2 };
    std::cout << "I have " << centsSum.getCents() << " cents.\n";

    return 0;
}
```

A similar process can be followed to overload the subtraction, multiplication and division operators too by defining functions for `operator-`, `operator*` and `operator/` respectively.

Note it is possible but not conventional to define friend functions within classes.

## Overloading operators for operands of different types

When C++ evaluates expression `x + y`, `x` is the first parameter and `y` is the second.
If they have different types, then we need to write overloaded functions to allow for all possibilities.

```cpp
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } {}

    // add Cents + Cents using friend function
    friend Cents operator+(const Cents& c1, const Cents& c2);

    int getCents() const { return m_cents; }
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } {}

    // add Cents + Cents using friend function
    friend Cents operator+(const Cents& c1, const Cents& c2);
    // add Cents + int using friend function
    friend Cents operator+(const Cents& c1, int value);
    // add int + Cents using friend function
    friend Cents operator+(int value, const Cents& c1);

    int getCents() const { return m_cents; }
};

// This function is NOT a member function
Cents operator+(const Cents& c1, const Cents& c2)
{
    return c1.m_cents + c2.m_cents;
}

Cents operator+(const Cents& c1, int value)
{
    return c1.m_cents + value;
}

Cents operator+(int value, const Cents& c1)
{
    // Could call operator+(c1, value) if result is same
    return value + c1.m_cents;
}

int main()
{
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents centsSum{ cents1 + cents2 };
    std::cout << "I have " << centsSum.getCents() << " cents.\n";

    return 0;
}
```

It is important to remember the order in which operators act to ensure the desired results.

It is possible to define overloaded operators by calling other overloaded operators and should do so if it produces simpler code.

## Overloading the I/O operators

This can be convenient for printing variables to a screen or getting variables from an input, both following a certain format.

### Overloading operator<<

Similar to overloading our arithmetic operators, the operand to the left of `<<` is a `std::cout` object and the operand to the right is our object of interest.
Since `std::cout` is a type of `std::ostream` object, our overloaded function will return a reference of type `std::ostream`.

```cpp
class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {}

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

    return out;
}
```

It is important to note the return type of `operator<<`.
We cannot return it by value since `std::ostream` specifically disallows copying and so it must be returned as a reference.
Note though that due to this, we can "chain" output commands together into one expression/line.

### Overloading operator>>

The input operator can be overloaded similarly to the output operator.
The main difference is that `std::cin` is an object of type `std::istream` and the reference to our class is no longer `const`.

```cpp
class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {}

    friend std::istream& operator<<(std::istream& in, Point& point);
};

std::istream& operator<<(std::istream& in, Point& point)
{
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_z;
    return in;
}
```

## Overloading the comparison operators

The comparison operators are an example of binary operators that do not modify their left operands, making friend functions a preferred method to modify them.

```cpp
#include <string>
#include <string_view>

class Car
{
private:
    std::string m_make;
    std::string m_model;

public:
    Car(std::string_view make, std::string_view model)
        : m_make{ make }, m_model{ model }
    {}

    friend bool operator==(const Car& c1, const Car& c2);
    friend bool operator!=(const Car& c1, const Car& c2);
};

bool operator==(const Car& c1, const Car& c2)
{
    return (c1.m_make == c2.m_make && c1.m_model == c2.m_model);
}

bool operator!=(const Car& c1, const Car& c2)
{
    return (c1.m_make != c2.m_make || c1.m_model != c2.m_model);
}
```

Note that you should only define overloaded operators that make intuitive sense for your class and usage.
For example, it would not make sense to define operators `<` or `>` as it doesn't make sense for a Car to be greater or less than another Car.

## Limitations

Not everything can be overloaded as a friend function.
Operators for assignment `=`, subscript `[]`, function call `()` and member selection `->` must be overloaded as member functions.

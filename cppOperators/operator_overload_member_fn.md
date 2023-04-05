# Overloading operators using member functions

Many operators can be overloaded as member functions.
The process is similar to using friend functions.

A few things to note when overloading using a member function:
- The overloaded operator must be added as a member function of the left operand.
- The left operand is the implicit `*this` object.
- All other operands become function parameters.

```cpp
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents }
    {}

    int getCents() const { return m_cents; }

    Cents operator+(int value);
};

Cents Cents::operator+(int value)
{
    // m_cents is from the implicit *this
    return Cents{ m_cents + value };
}
```

## Overloading unary operators

It is preferable to overload unary operators using member functions as they only operate on the object they are applied to.
Examples of unary operators include the positive `+`, negative `-` and logical not `!` operators.


```cpp
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents }
    {}

    Cents operator-() const;
    // const as operator- does not modify the Cents object

    int getCents() const { return m_cents; }
};

Cents Cents::operator-() const
{
    return -m_cents;
    // return type is Cents so implicity converts from int to cents using the Cents(int) constructor
}
```

### Overloading the increment and decrement operators

It is fairly straightforward to overload the increment `++` and decrement `--` operators; however, it is important to bear in mind they each have two versions: prefix and postfix.

Overloading their prefix versions is done in the same way overloading normal unary operators:

```cpp
class Digit
{
private:
    int m_digit{};

public:
    Digit(int digit=0) : m_digit{ digit }
    {}

    Digit& operator++();
};

Digit& Digit::operator++()
{
    if (m_digit == 9)
        m_digit = 0;
    else
        ++m_digit;

    return *this; // return *this to allow operators to be chained 
}
```

To overload their postfix versions, we denote our operators to have an `int` parameter.
This is how the compiler distinguishes between the prefix and postfix overloads of the increment and decrement operators.

```cpp
class Digit
{
private:
    int m_digit{};

public:
    Digit(int digit=0) : m_digit{ digit }
    {}

    Digit& operator--();
    Digit& operator--(int);
};

Digit& Digit::operator--()
{
    if (m_digit == 0)
        m_digit = 9;
    else 
        --m_digit;

    return *this;
}

Digit& Digit::operator--(int)
{
    Digit temp{ *this }; // create temp variable with current digit
    --(*this); // decrement using prefix operator

    return temp; // return saved state
}
```

Because do not name the `int` dummy parameter for the post fix operator, the compiler treats this variable as a placeholder and so does not warn us when such a variable is declared but not used.

Note that postfix operators are typically less efficient that prefix operators due to the added overhead of instantiating a temporary variable and returning by value rather than by reference.

## Overloading the subscript operator

If we have a class that contains a private member variable that is an array, it is not possible to access it to get or set functions without creating access functions.
Although this works, it can be difficult and confusing to work with.

In cases like these, it can be better to overload the subscript operator `[]` in order to allow access to the elements of our private member array.

```cpp
#include <cassert>
#include <iterator>

class IntList
{
private:
    int m_list[10]{};

public:
    int& operator[](int index);
};

int& IntList::operator[](int index)
{
    // Optional line for checking index within bounds
    assert(index >=0 && index < std::size(m_list));

    return m_list[index]
}
```
Now the compiler returns the corresponding element from the `m_list` member variable without the need for a clunkier access function.
This allows us to get and set values of `m_list` directly.

It is also possible to define a separate `const` version of `operator[]` if our object was `const`.

C++23 will add support for overloading `operator[]` with multiple subscripts.

Note that pointers to objects and the overloaded operator `[]` do not mix as the compiler assumes you are trying to index an array of objects of the pointer type (remember that arrays implicitly collapse into pointers).
The proper syntax would be to dereference the pointer first before calling `operator[]`.

```cpp
int main()
{
    IntList* list{ new IntList{} };
    (*list)[2] = 3; // get IntList object then call overloaded operator
    delete list;

    return 0;
}
```

It should also be noted that the function parameter of `operator[]` does not have to be `int` which opens up the potential for different (e.g. `std::string`) parameters that can be used to index arrays.

## Overloading the parenthesis operator

Unlike other overloaded operators, the parenthesis operator `()` can vary in both the type and number of parameters it can take.
This means it can be extremely flexible and have multiple use cases.

```cpp
#include <cassert>
class Matrix
{
private:
    double m_data[4][4]{};

public:
    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    void operator()();
};

double& Matrix::operator()(int row, int col)
{
    assert(0 <= col && col < 4);
    assert(0 <= row && col < 4);

    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    assert(0 <= col && col < 4);
    assert(0 <= row && col < 4);

    return m_data[row][col];
}

void Matrix::operator()()
{
    // Reset all matrix elements to 0.0
    for (int row{ 0 }; row < 4; ++row)
    {
        for (int col{ 0 }; col < 4; ++col)
        {
            m_data[row][col] = 0.0;
        }
    }
}
```

Here, overloading `operator[]` is insufficient as it only allows access to a private one-dimensional array where we want to access a private two-dimensional array.
Because `operator()` has no limit on the number of parameters passable, we can declare a version that takes two integer index parameters in order to access our array.

We can also create other overloads that act differently on our object (although it would be clearer to create a member function called `erase()` in the last case).

Due to its versatility, `operator()` is commonly overloaded to implement functors, otherwise known as function objects.
These are classes that operate like functions with their main advantage being that they can store data in member variables.

## Overloading the copy assignment operator

`operator=` is used to copy values from one object to another *already existing object*.

This is slightly different from a copy constructor which copies by intialising new objects.

```cpp
#include <cassert>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        assert(denominator != 0);
    }

    // Copy constructor
    Fraction(const Fraction& copy)
        : m_numerator{ copy.m_numerator }
        , m_denominator{ copy.m_denominator }
    {}

    // Overloaded assignment operator
    Fraction& operator=(const Fraction& fraction);
};

Fraction& Fraction::operator=(const Fraction& fraction)
{
    // Perform copy to this object
    m_numerator = fraction.m_numerator;
    m_denominator = fraction.m_denominator;

    // return *this to allow chaining of multiple assignement operators
    return *this;
}
```

Be wary that problems can arise since C++ allows self-assignment (e.g. `x = x`).
This usually occurs when an assignment operator needs to dynamically assign memory and there is potential for memory leaks and dangling pointers in the process.
It is possible to check if the address of our implicit object is the same as that of the object being passed in as a parameter to safeguard against this.
Although not always needed, it is important to be aware of guarding against self-assignement.

Unlike other operators, the compiler provides a default public copy assignment operator for your class if you do not provide one that does memberwise assignment.
Similar to other constructors and operators, assignments can be prevented either by making the copy assignment operator private or setting the overload equal to the `delete` keyword.



## Limitations

Operators which must be added as a member of the left operand cannot be overloaded as member functions.

For example, if the left operand is an object of type `std::ostream` which is fixed as part of the standard library, the class declaration can't be modified to add the overload as a member function of `std::ostream`.
This means `operator<<` must be overloaded as a normal (preferred) or friend function.

Typically, member overloads can't be used if the left operand is either not a class (e.g. `int`) or is a class we can't modify (e.g. `std::ostream`).

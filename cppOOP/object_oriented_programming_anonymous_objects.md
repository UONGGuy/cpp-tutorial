# Object-Oriented Programming: Anonymous Objects

An anonymous object is essentially a value with no name.
This means there's no way to refer to them beyond their point of creation and so have "expression scope": they are created, evaluated and destroyed within a single expression.

These are primarily used to avoid the mass creation of many temporary variables when passing or returning values.
Dynamically allocated memory is also done anonymously (which is why its affress must be assigned a pointer to refer to it).

```cpp
int add(int x, int y)
{
    return x + y; // an anonymous object is created to hold and return the result of x + y
}
```

In the example, `x + y` is evaluated with the result being placed in an anonymous object which is returned to the caller by value and then destroyed.

Anonymous objects occur in function parameters as well as return values and keeps code more concise.

## Anonymous class objects

It is possible to construct anonymous objects of user-defined class types which is done by creating objects as normal but without giving a variable name.

```cpp
Cents cents{ 5 }; // normal variable object
Cents{ 7 }; // anonymous object
```

Although it may not seem that useful for now, it can be useful when simplifying more complex code.

```cpp
#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents }
    {}

    int getCents() const { return m_cents }
};

Cents add(const Cents& c1, const Cents& c2)
{
    return { c1.getCents() + c2.getCents() }; // return anonymous Cents object
}

int main()
{
    std::cout << "I have " << add(Cents{ 6 }, Cents{ 8 }).getCents() << " cents.\n"; // prints anonymous Cents value

    return 0;
}
```

Because anonymous objects have expression scope, they can only be used once unless bound to a constant l-value reference.
If the value needs to be referenced in multiple expressions, it is better to use a named variable instead.

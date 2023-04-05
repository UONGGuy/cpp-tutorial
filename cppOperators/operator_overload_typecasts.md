# Overloading typecasts

It is possible to tell C++ how to convert between built-in data types and our own user-defined classes using user-defined conversions.

This allows us to explicitly cast our classes and gives the compiler the ability to implicitly cast classes as built-in data types too.

Key differences to bear in mind comparing to overloading as a member function:
- The overload function is written in our class and called `operator <type>()`. There is a space between the `operator` keyword and the type we cast to.
- The overload function must be a non-static member.
- No parameters are taken as there is no way to pass an argument to the user-defined conversion.
- User-defined conversions do not have a return type (C++ assumes you will return the correct type).

```cpp
class Cents
{
private:
    int m_cents;

public:
    Cents(int cents=0) : m_cents{ cents }
    {}

    // Overloaded int cast
    operator int() const { return m_cents; }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};
```

Now the following is allowed:

```cpp
Cents cents{ 7 };
int c{ static_cast<int>(cents) };
std::cout << cents;
```

It should be pointed out that it is possible to cast one class to another.

## Comparison to converting constructors

Converting constructors and overloaded typecasts play similar roles.
A converting constructor allows us to define a function creating a user-defined type A from another type B.
Overloaded typecasts convert user-defined type A into another type B.

In general, converting constructors should be preferred to overloaded typecasts as they allow the type being constructed to own the construction.

However, overloaded typecasts are preferred in the following situations:
- Providing a conversion to a fundamental type (usually to bool).
- Providing a conversion to a type you can't add members to (e.g. conversion to a class in the standard library like `std::vector`).
- When you don't want the type being constructed to be aware of the type being converted to (helpful for avoiding circular dependencies).

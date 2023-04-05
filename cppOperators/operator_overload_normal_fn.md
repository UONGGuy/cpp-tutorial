# Operator overloading with normal functions

Overloaded operators can be written as normal functions.
This is similar to overloading operators using friend functions but with a different level of access to private members.

Note that when overloading operators using normal functions, you may have to provide your own function prototype, unlike with friend functions.

```cpp
#ifndef CENTS_H
#define CENTS_H

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents }
    {}

    int getCents() const { return m_cents; }

};

// Prototype must be explicitly provided for operator+ so uses of 
// operator+ in other files are aware of this overload's existence
Cents operator+(const Cents& c1, const Cents& c2);

#endif
```

Normal functions are generally preferred over friend functions to minimise unnecessary access to private members, but it should not be the case that you add additional access functions just to achieve this.



# Object-Oriented Programming: const class objects and member functions

## Const member functions

Classes can be made cobnst using the `const` keyword.
This is done by initialising `const` class constructors.

```cpp
const Date date1; // initialise with default constructor
const Date date2(2023, 03, 10); // initialise with parameterised constructor
const Date date3{ 2020, 10, 16 }; // initialise with parameterised constructor (C++11)
```

Once a const class is initialised, it is not possible to modify its memver variables - whether that be directly or by calling member functions.

## Const member functions

If a const class is initialised, only const member functions can be called - even if the member function does not change any member variables.

A const member function is one that guarantees it wll not modify the object or call any non-const member functions.

To define a const member function, the `const` keyword needs to be appended to the function prototype, after the parameter list but before the function body.

```cpp
class Something
{
public:
    int m_value{};

    Something() : m_value{ 0 } {}

    void resetValue() { m_value = 0; }
    void setValue(int value) { m_value = value; }
    int getValue() const { return m_value; } // notice placement of const keyword
};
```

For member functions defined outside the class function, the `const` keyword must be used on both the function prototype in the class definition and the function definition.

```cpp
class Something
{
public:
    int m_value{};

    Something() : m_value{ 0 } {}

    void resetValue() { m_value = 0; }
    void setValue(int value) { m_value = value; }
    int getValue() const; // notice placement of const keyword
};

int Something::getValue() const
{
    return m_value;
}
```

Any const member function attempting to change a member variable or call a non-const member function will incurr a compiler error.

Note that constructors cannot be marked as const in the code since they need to intialise member variables.
It is also important to mention const members cannot return non-const references to members, only const referene.

Best practice is to make all member functions that do not modify the state of the class object const so they can be called by const objects.

## Passing by const reference

A common way to get a const object is by passing an object to a function by const reference.

It is important to remember that any member functions to be used during this need to be const member functions.

## Overloading const and non-const functions

It is possible to overload a function such that it has a const and non-const version.
This works as the const qualifier is considered part of the function's signature and so the two are distinguishable.

```cpp
#include <string>

class Something
{
private:
    std::string m_value{};

public:
    Something(const std::string& value="") : m_value{ value } {}

    // getValue() for const objects, returning const reference
    const std::string& getValue() const { return m_value; }
    // getValue() for non-const objects, returning non-const reference
    std::string& getValue() { return m_value; }
};
```

Overloading with a const and non-const version is usually done if the return value needs to differ in const-ness.
Here, the non-const version of `getValue()` allows us to read and write `m_value`.

Because passing objects by const reference is common, your classes should be const-friendly (i.e. make non-modifying member functions const!)

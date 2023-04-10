# Inheritance functionality

One of the biggest benefits of using derived classes is the ability to reuse already written code.
It is possible to inherit base class functionality and add new functionality, modify functionality, or hide unwanted functionality.

```cpp
#include <iostream>

class Base
{
protected:
    int m_value{};

public:
    Base (int value): m_value{ value }
    {}

    void identify() const { std::cout << "I am a Base\n"; }
};

class Derived: public Base
{
public:
    Derived(int value): Base{ value }
    {}
};
```

## Adding new functionality

It is possible to add new functionality to a derived class by declaring it in the derived class as normal (e.g. create new member functions).

```cpp
class Derived: public Base
{
public:
    Derived(int value): Base{ value }
    {}

    int getValue() const { return m_value; }
};
```

## Calling inherited functions

Derived classes inherit all base class behaviours by default.

When a member function is called with a derived class object, the compiler first checks if it exists in the derived class before working up the inheritance chain until it finds a match.
It will use the first instance of the function it can find.

## Overriding behaviour

If a function is redefined in the derived class, it does not inherit the access specifier for the function with the same name in the base class - it uses the access specifier it is defined under in the derived class.

## Adding to existing functionality

It is possible to add functionality to a member function called by a class further up the inheritance chain instead of hiding it with a new function in the derived class.
We can write a function of the same name in the derived class and call the base class version with the scope qualifier before adding additional functionality.

```cpp
#include <iostream>

class Derived: public Base
{
public:
    Derived(int value) : Base{ value }
    {}

    int getValue() const { return m_value; }

    void identify() const
    {
        Base::identify();
        std::cout << "I am a Derived\n";
    }
};
```
Sometimes you may encounter issues trying to call friend functions in base classes.
This is because friend functions of the base class aren't actualy a part of the base class so the scope resolution qualifier doesn't work here.
To get around this, it is best to cast the object explicitly as the base class using `static_cast<const Base&>` so the correct version of the function works.

## Changing an inherited member's access level

It is possible to change an inherited member's access specifier in the derived class with the `using` declaration.

```cpp
#include <iostream>

class Base
{
private:
    int m_value{};

public:
    Base (int value): m_value{ value }
    {}

protected:
    void printValue() const { std::cout << m_value; }
};

class Derived: public Base
{
public:
    Derived(int value): Base{ value }
    {}

    // make Base::printValue public
    using Base::printValue; // note there are no parentheses at the end
};
```

Note that you can only change the access specifiers of base members the derived class is normally able to access.

## Hiding functionality

It is not possible to remove or restrict functionality from a base class without modifying the source code for a base class.
However, in a derived class, it is possible to hide functionality that exists in the base class to prevent it being accessed via the derived class.
This can be done by changing the relevant access specifier (e.g. make public member private).

Note that although members can be specified as private in the derived class, they will still retain their original specifier in the base class meaning they can still be accessed by casting the derived class to the base class and directly accessing the member.

It is possible to mark member functions from the base class as deleted in the derived class to prevent them being called through a derived object entirely.

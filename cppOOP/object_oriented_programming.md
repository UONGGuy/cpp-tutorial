# Object-Oriented Programming

OOP gives us a way of defining objects with both properties and behaviours contained in a reusable package.
It helps make code clearer and can change the way functions are written due to having a well-defined set of behaviours.

This allows programs to be written in a more modular and intuitive fashion.

Additional concepts that OOP brings include:
- Inheritance
- Encapsulation
- Abstraction
- Polymorphism

Despite their similarities to structs, it is recommended that the `struct` kkeyword should be used for data-only structures and the `class` keyword for objects with both data and functions.

## Classes and class members

The `class` keyword defines a type that is similar to a struct but contains a reference to the data rather than the value itself (which is what a struct does).
Classes also use heap allocation rather than stack allocation.
They are initialised similarly to structs:

```cpp
struct DateStruct
{
    int year{};
    int month{};
    int day{};
};

class DateClass
{
public:
    int m_year{};
    int m_month{};
    int m_day{};
};
```

By convention, class names should begin with an upper-case leter.

### Specifiers

We note that there is the `public` keyword in our comparison example of a class vs a struct.

Structs are public by default meaning its means members can be accessed directly by anyone - including code that exists outside the struct definition.
Class members are private by default meaning they cannot be accessed by the public - they can only be accessed by other memebers of the class.
The `public` keyword is an access specifier that makes class members public.

The group of public members of a class are often referred to as a public interface.

C++ has 3 different access specifiers: public, private and protected.

We will cover the protected access specifier in inheritance.

In general, member variables are usually made private and member functions made public unless there is good reason not to.

It is also important to note that access control works on a per-class basis,not a per-object basis.
This means when a function has access to the private members of a class, it can access the private members of **any** object of that class type that it can see.
This is useful when we need to copy members from one object of a class to another of the same class.

### Member functions

Functions defined inside a class (or struct) are called member functions or methods.
These can be defined inside or ouside the class definition.
Members of a class can be accessed just like they are in structs - using the member selection operator `.`.

```cpp
#include <iostream>

class DateClass
{
public:
    int m_year{};
    int m_month{};
    int m_day{};

    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    DateClass today{ 2023, 02, 26 };

    today.m_day = 16;
    today.print();

    return 0;
}
```

Since all member function calls are associated with an object of the class, we don't need to explicitly pass the class into the member function like we would if it was a struct.
The associated object is implicitly passed to the member function and so is often called the implicit object.

By using the "m\_" prefix, we distinguish member variables from function parameters or local variables inside member functions.

Unlike with normal functions, we don't need to be concerned about the order in which member functions are declared for the compiler to see.

### Member types

Classes can also have member types or nested types (including type aliases).

In these contexts, the class name acts like a namespace for the nested type.

Nested types cannot be forward declared.
They should only be used when they are exclusive to that class.

It is possible to nest classes within other classes if desired.

## Encapsulation

Also called information hiding, encapsulation hides the process of how an object is implemented from users of the object.
We can implement encapsulation via access specifiers `private`.

There are many benefits of encapsulation:
- Encapsulated classes are easier to use and reduce program complexity as you only need to know how the member functions work, not how they are implemented.
- Data is protected, preventing misuse.
- Encapsulated classes are easier to change without program-wide problems occurring (e.g. renaming variables, changing implementation but methods still do the same thing).
- Encapsulated classes are easier to debug as everyone has the same call to the function so it is easier to breakpoint where member variables are changed.

### Access functions

Access functions are short public functions whose jobs are to retrieve or change the value of a private member variable.
There are two types of access functions:
- Getters/accessors: functions that return the value of a private member variable.
- Setters/mutators: functions that set the value of a private member variable.

Getters should provide "read-only" access to data so it is best practice to have them return by value or const reference.

When making classes, consider the following:
- If nobody outside your class needs to access a member, don't provide access functions for it.
- If someone outside your class needs to access a member, think about whether you can expose a behaviour or action instead (e.g. rather than a setAlive(bool) setter, implement a kill() function instead)
- If you can't, consider whether you can provide only a getter.


# Structs

Structs are user-defined types that are useful when we want to bundle multiple variables together into a single type.
This allows related sets of variables to be managed more easily.

## Definings structs

Using keyword `struct`, we can define a struct and inside the curly braces we define variables to hold the information that we want it to contain (these are called data members or member variables).
Like enumerations, a semi-colon is used to signal the end of a struct definition.

```cpp
struct Employee
{
    int id{};
    int age{};
    double wage{};
};
```

To access members of an initialised struct object, we call the object with the member selection operator `.<member name>`.

```cpp
struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee jane;

    jane.age = 24;

    std::cout << jane.age << '\n';

    return 0;
}
```

Structs make it easy to tell which member variables belong to which objects, allowing for a higher level of organisation.

## Aggregate initiatialisation

Data members for structs are not initialised by default.
When this is the case, undefined behvaiour can occur when they are called.

An aggregate data type is one that can contain multiple data members.
For struct objects, we can use aggregate initialisation to initialise members of the struct directly.
This is done by providing an initialiser list as an initialiser.

```cpp
struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee jane = { 1, 24, 60000.0 }; // copy-list intialisation using braced list
    Employee john ( 2, 45, 55000.0 ); // direct initialisation using parenthesised list
    Employee joe { 3, 32, 45000.0 }; // list initialisation using braced list (preferred)

    return 0;
}
```

Each of these initialisation forms does memberwise initialisation (i.e. each ember initialised in order of declaration).

Best practice is to prefer non-copy brace listed form when initialising aggregates.

If the number of initialisation values is fewer than the number of members, then all remaining members are value initialised.
This means we can use an empty initialisation list to value-initialise all members of the sturct.

## Designated initialisers

If we wanted to use aggregate initialisation but specifically assign values to certain struct members, C++20 allows the use of designated initialisers.
When doing this, it is important to initialise members in the same order in which they are declared in the struct to avoid errors occuring.
Members not designated an initialiser will be value initialised.


```cpp


## Const structs

Variables of the struct type can also be const and are initialised in the same way as other const varaibles - by using the `const` keyword.

```cpp
struct Foo
{
    int a{};
    int b{};
    int c{};
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // allowed: f1.a = 1, f1.b = 0 (value initialised), f1.c = 3

    Foo f2{ .b{ 2 }, .a{ 1 } }; // error: initialisation order doesn't match order of declaration in struct

    return 0;
}
```

Designated initialisers are useful as they provide some level of self-documentation and prevent values being misassigned - especially when updating structs with new members.

Despite this, it is probably best practice to recommend adding new members to the bottom of the definition list to prevent shifting the positions of existing members since designated initialisers can clutter code significantly.

## Default member initialisation

Also called non-static member initialisation, allows a default value to be provided for each member as part of the type definition.
To do this, specify the default value in the member initialisation of the struct definition.

Explicit initialisation always takes precedence over default member initialisation values.
If an aggregate is initialised with less values than there are members, all remaining numbers are value-initialised unless they have default values which take precedence.

It is best practice to always provide a default value for all members to avoid errors associated with uninitialised variables.

Always try to value initialise aggregates over default initialising them.

## Passing structs

An advantage of using structs is that the entire sruct can be passed to a function that requires its members to work.
Structs are usually passed by (const) reference to avoid making copies.

```cpp
void printEmployee(const Employee& employee) // pass by reference
{
    std::cout << "ID: " << employee.id << '\n';
    std::cout << "Age: " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}
```

This means the function call or declaration won't need changing to acommodate new members to the struct.

## Returning structs

Structs are usually returned by value to avoid returning dangling references.
Due to the struct type being specified at function declaration, it is possible to just return the struct values as a braced list if desired.

## Structs with user-defined members

It is possible for structs (and classes) to contain members that are also user-defined types.

To do this, we can define a user-defined type in the global scope and then use it as a member of another user-defined type.

To initialise a struct within a struct, we nest the inner struct's brace initialier within the outer struct's initialisation braces.

```cpp
struct Employee // could define this within Company struct
{
    int id{};
    int age{};
    double wage{};
};

struct Company
{
    int numberOfEmployees{};
    Employee CEO{}; // Employee struct within Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 70000.0 } }; // nested initialisation list for Employee struct

    return 0;
}
```

### Struct size and data structure alignment

Struct size is typically the sum of the sizes of all its members, but not always.
Sometimes the compiler will add gaps into structures (padding).
This means struct size will be at least as large as the sum of its member sizes.

## Member selection with pointers and references

We can use the member selection operator (`.`) to access a member from a reference to a struct.

However, this does not work on a pointer to a struct.
In order to use the member selection operator, the pointer must be dereferenced in parentheses first (to ensure it occurs first).
A clearer alternative is to use the member selection from pointer operator `->` (sometimes called the arrow operator.

```cpp
#include <iostream>

struct Employee
{
    // as before
};

int main()
{
    Employee jane{ 1, 25, 65000.0 };

    Employee* ptr{ &jane };

    std::cout << (*ptr).id << "\n"; // original but less clear method
    std::cout << ptr -> id << "\n"; // better method with greater clarity

    return 0;
}
```

The member selection operator is always applied to the currently selected variable.
If there is a mix of pointers and normal member variables, it is clearer to see which selections occur where `.` and `->` are used in sequence.



# Lvalue references

References in C++ are aliases for existing objects.
Any operation on an object's reference is also applied to the object itself.
It is possible to pass references to functions which can be less expensive than making copies of arguments in some cases.

There are two types of references in modern C++: lvalue references and rvalue references.

## Lvalue reference types

Commonly just called references, they act as aliases for existing lvalues (e.g. variables).

The ampersand `&` is used in type declaration to declare an lvalue reference type.

Using an lvalue reference type, an lvalue reference variable can be created.
This is essentially a variable that acts as a reference to the lvalue in question (usually another variable).

```cpp
#include <iostream>

int main()
{
    int x{ 5 }; // normal int variable
    int& ref{ x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n'; // prints the value of x
    std::cout << ref << '\n'; // prints the value of x via ref
    // both results print 5

    return 0;
}
```

Best practice is to place the ampersand next to the type (`int& ref`) rather than the reference variable's name (`int &ref`) although this is also valid.

Since references are aliases for their variables, any changes that are applied to them are also applied to the variable.

### The ampersand (&) in C++

The ampersand (&) tends to cause confusion because it has different functions depending on usage:
- When using following a type name, it denotes an lvalue reference: `int& ref`
- When used in a unary context in an expression, it is the address-of operator (returns memory address of variable): `std::cout << &x`
- When used in a binary context in an expression, it is the bitwise AND operator: `std::cout << x & y`.

It is worth noting that when used as the address-of operator, the memory address is returned as a pointer containing the address rather than a literal.

## Lvalue reference initialisation

All references must be initialised similar to constants.

Once initialised with an object or function, we say the reference is bound to it with the object sometimes called the referent.

Lvalue references can only be bound to modifiable lvalues.
These are also called non-const references since interacting with them allows their value to be changed.

In most cases, the reference must match the type of the referent (with some exceptions - see inheritance).

Lvalue references to void are disallowed.

Once initialised, references cannot be reseated (i.e. cannot be changed to reference another object).

Although references are aliases for objects, they are not objects themselves.
Due to this, they can't be used anyhwere an object is required (e.g you can't have a reference to a reference).
In the case you need a reference that is an object or a reference that can be reseated, `std::reference_wrapper` is a solution.

### Lvalue reference scope and duration

Reference variables follow the same scoping and duration rules as normal variables.
However, references and referents have independent lifetimes with one exception.
This means a reference can be destroyed before its referent and vice versa.

If an object with a reference is destroyed, it leaves behind a dangling reference which can lead to undefined behaviour if accessed.

## Lvalue references to const

Although we mentioned that lavlue references can only be bound to modifiable objects, we can bind lvalue references to const variables (which are non-modifiable lvalues).

```cpp
const int x{ 5 }; // const => x is non-modifiable
const int& ref{ x }; // ref is an lvalue reference to a const value
```

Although an lvalue reference can be made to a const variable, they cannot be modified - only accessed.

It is possible to initialise a const lvalue reference (e.g. `const int& ref{ x }`) where the variable can only be modified if it is called directly and not through its const reference.

It is best to favour lvalue references to const over lvalue references to non-const unless it's necessary to modify the object being referenced.

## Initialising an lvalue reference to const with an rvalue

Lvalue references to const can also bind to rvalues.

```cpp
const int& ref{ 5 }; // valid reference although 5 is an rvalue
```

During this process, a temporary object is created and initialised with the rvalue.
The reference to const is then bound to the temporary object.

Temporary objects are objects created for use within a single expression which are then destroyed.
They have no scope (as they do not have identifiers) and so can only be used directly at the point of creation.

If a const reference is bound to a temporary object, its lifetime is extended to match that of the const reference.
This is to avoid leaving references dangling which leads to undefined behaviour when trying to access the them.

## Pass by reference

Usually, it is the case that a copy of the argument is made and passed to the function parameter.
However, for some types like `std::string`, it can be more expensive to create a copy of the argument to be used in the function.
By instead defining the parameter type to be an lvalue reference (e.g. `std::string&`), we can avoid creating a copy of such arguments.
Binding lvalue references is always inexpensive and avoids making copies whilst acting similarly.

Note that since lvalue references are aliases to the original object, passing values by reference to non-const to functions can lead to modifications to the object being referenced which may or may not be useful.

It is also important to remember passing by reference to non-const can only accept modifiable lvalue arguments.

To get around this, we can pass by const reference.
By making the reference parameter const, it is able to bind to any type of argument.
This means the function will not be able to modify the value being referenced.

It is best practice to pass fundamental, enumerated and `std::string_view` types by value as they are inexpensive and to pass class or struct types by const reference.

## Return by reference

It is also possible to return a reference that is bound to the object returned by a function.
This avoids making a copy of the return value.

To do this, we define the return value of the function to be a reference type.

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // returns a const reference
{
    static const std::string s_programName{ "Calculator" }; // static duration => destroyed at end of program

    return s_programName;
}

int main()
{
    std::cout << "This program is called " << getProgramName();

    return 0;
}
```

Since the function returns a const reference type, when the object in the function is returned, the function itself returns a const reference to it.

The caveat to this method is that the object being referenced must outlive the function returning the reference, otherwise the reference will be left dangling.
As such, local variables should never be returned by reference.
It is fine to return reference parameters by reference since in order to do this, the argument must exist in the scope of the caller and so outlive the function (e.g. function taking in two reference parameters, comparing them and returning the larger one by reference).

The returned reference can be used to assign or initialise a normal variable.

Similar to how functions can modify arguments passed by non-const references, the caller can modify values returned by non-const reference from a function.



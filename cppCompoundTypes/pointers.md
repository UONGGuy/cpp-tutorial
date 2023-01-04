# Pointers

Pointers are objects that hold memory addresses as their values and are important features of C++.
They behave similarly to lvalue references allowing objects to be accessed and modified in similar ways.

In best practice though, it is better to favour references over pointers unless the extra capabilities of pointers are required.

Pointers are declared with the dereference operator (\*).
```cpp
int; // an int variable
int&; // an lvalue reference to an int value
int*; // a pointer to an int value (object holding the address of an int value)
```

## The dereference operator (\*)

We can find the memory address of a variable using (&) but it isn't very useful by itself.

The derefence (indirection) operator (\*) takes a memory address and returns the object located there.
If we it in combination, then the value at the given memory address is returned as an lvalue.

```cpp
#include <iostream>

int main()
{
    int x{ 7 };
    
    std::cout << x << '\n'; // prints value of x
    std::cout << &x << '\n'; // prints memory address of x
    std::cout << *(&x) << '\n'; // prints value at the memory address of variable x (parenthesis for clarity, but not necessary)
    
    return 0;
}
```

Changing the value of a dereferenced pointer modifies the value of the object located at that memory location.

## Pointer intialisation

Pointers are not initialised by default.
Uninitialised (wild) pointers contain garbage addresses and dereferencing wild pointers will result in undefined behaviour.
As such, pointers should always be initialised to known values.

```cpp
#include <iostream>

int main()
{
    int x{ 8 };

    int* ptr; // uninitialised pointer
    int* ptr2{}; // null pointer
    int* ptr3{ &x }; // pointer initialised with address of variable x

    std::cout << *ptr3 << '\n'; // returns value at the address contained by ptr3

    return 0;
}
```

It is not allowed to initialise pointers with literal values, bar one exception.

## Assignment with pointers

Assignment with pointers can be used in two ways:
- To change what the pointer is pointing at (assign a new address to the pointer)
- To change the value being pointed at (assign the dereferenced pointer a new value)

### Comparison with lvalue references

Pointers and lvalue reference can access and modify objects in similar ways.
However, there are some key differences:
- References must be initialised, pointers don't have to (but should) be.
- References are not objects, pointers are.
- References cannot be reseated (changed to reference something else), pointers can change what they point at.
- References must always be bound to an object, pointers can point to nothing.
- References are "safe" (outside of dangling references), pointers are inherently dangerous.

### Pointer size

Pointer size depends on the architecture the executable is compiled for (e.g. 32-bit machine -> pointer size is 32 bits).
This is true regardless of the size of the object being pointed to.

## Dangling pointers

Dangling pointers hold addresses of objects that are no longer valid (e.g. because they have been destroyed).
Dereferencing dangling pointers leads to undefined behaviour.

## Null pointers

When a pointer holds a null value (i.e. no value), it does not point at anything.

A pointer can either be initialised as null or assigned and passed as such using `nullptr` keyword.

```cpp
int* ptr{}; // initialise a null pointer
int* ptr2{ nullptr }; // initialise a null pointer

int value{ 5 };
int* ptr3{ &value };
ptr3 = nullptr; // make ptr3 a null pointer
```

In older code, the literal `0` or preprocessor macro `NULL` (defined in the <cstddef> header)  may be used instead of `nullptr`.

Dereferencing null pointers leads to undefined behaviour.
Despite this, it is best practice to set dangling pointers to `nullptr` as using Boolean conditionals, we can test whether a pointer has value `nullptr` or not.

It is also worth noting pointers have implicit Boolean conversions `true` if non-null, `false` if null).

## Pointer to a const value

To declare a pointer to const, we need to use the `const` keywords when initialising it.

Note that a pointer to const is not const itself - it just points to a const value.
It is possible to assign a new address to the pointer.

Similar to a reference to const, a pointer to const can also point to non-const variables regardless of whether the object at the address was initially defined as const or not.

```cpp
const int x{ 6 };
const int* ptr{ &x }; // pointer to const int x

const int y{ 7 };
ptr = &y; // ptr now points to const int y

int z{ 8 };
ptr = &z; // ptr now points to variable int z
```

## Const pointers

It is also possible to make a pointer itself constant by using the `const` keyword after the typing of the pointer.
Const pointers cannot have their addresses changed after initialisation.

```cpp
int x{ 12 };
int* const ptr{ &x }; // const pointer
```

Notice though that if the value being pointed to is non-const then it is possible to change the value being pointed to via dereferencing.

It is also possible to declare a const pointer to a const value.
In this case, the pointer's address cannot be changed and the value cannot be modified through the pointer.

```cpp
int x{ 12 };
const int* const ptr{ &x }; // const pointer
```

## Pointer usage overview

In summary,

- A non-const pointer can be assigned another address to change what it points at
- A const pointer always points to the same address (which cannot be changed)
- A pointer to a non-const can change the value it points to but cannot point to a const value.
- A pointer to a const cannot change the value it points to but can point at both const or non-const lvalues (but not rvalues which do not have an address)

## Passing arguements to functions by address

Arguments to functions can also be passed by their address (via a pointer).
The function is able to dereference the pointer in order to access the object whose address was passed.

Passing by address does not make a copy of the object being pointed to, similar to passing by reference.
A copy of the pointer which holds the object's address is made so it is always fast as addresses are typically small in size (4 or 8 bytes).
Note it is also possible to pass pointers by reference.

Passing by address allows the object's value to be modified by the function.
If we do not want the object to be modified, the function parameter can be made a pointer to const instead.

It is important to check the pointer being passed is non-null to avoid undefined behaviour.
This can be done using an assert or conditional statement as mentioned before.

In general, it is better to pass by reference rather than passing by address as passing by (const) reference can do the same job and more flexibly (accepts lvalues and rvalues).
Only pass by address if you have a specific reason to do so.

One common use for passing by address is to allow functions to accept optional arguments like the example below.

```cpp
#include <iostream>
#include <string>

void greet(std::string* name=nullptr)
{
    std::cout << "Hello ";
    std::cout << (name ? *name : "guest") << '\n';
}

int main()
{
    greet(); // name unknown

    std::string user{ "Mysterious person" };
    greet(&user);

    return 0;
}
```

However, in general function overloading tends to be the better alternative when looking to achieve the same result.

## Returning by address

Returning by address works similarly to returning by reference but a pointer to an object is returned instead of a reference to an object.

The caveat that the object whose address is being returned must outlive the function also applies in this case.

The advantage of return by address over return by reference is that the function can return `nullptr` if there is no valid object to return.
However, this also means it is important to remember to do a `nullptr` check to avoid undefined behaviour when dereferencing the return value.

As such, return by reference should be preferred over return by address unless the ability to return "no object" is required.


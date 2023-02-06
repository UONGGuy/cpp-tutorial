# Dynamic memory allocation

C++ supports three basic types of memory allocation:
- **Static memory allocation** (for static and global variables): Memory is allocated once the program is run and persists through program lifetime.
- **Automatic memory allocation** (for function parameters and local variables): Memory is allocated when the relevant block is entered and freed when the block is exited. Occurs as many times as necessary.
- **Dynamic memory allocation** (for variables that need memory allocated in run time): Used when the size of variable isn't known at compile time and/or when we want to manually control when memory allocation/deallocation occurs.

Dynamic memory allocation is usually used when dealing with external (user or file) inputs and allows programs to request memory when they need it.
It minimises wasted memory and prevents limitations or overflows.

Most normal variables are allocated in a portion of memory called the stack.
Stack memory for a program is usually small and if exceeded, can cause overflow and the OS to close the program.
For dynamic memory allocation, programs request memory from the heap - a larger pool of memory managed by the OS.

Unlike in static or automatic allocation, the program is responsible for requesting and disposing of dynamically allocated memory.

## Dyamic allocation of single variables

To dynamically allocate a single variable, use the scalar (non-array) form of the `new` operator:

```cpp
new int; // dynamically allocate an int and discard the result
```

The example above requests an integer's worht of memory from the OS.
The `new` operator creates the object using the memory and returns a pointer containing the address of the memory allocated.

More often than not, we will assign a return value to our own pointer variable to access the allocated memory later.

```cpp
int* ptr{ new int }; // dyn allocate an int and assign address to ptr
```

This allows indirection through the pointer to be used to access the memory.

### Initialising a dynamically allocated variable

Dynamically allocated variables can be initialised via direct or uniform initialisation.

```cpp
int* ptr1{ new int(5) }; // direct initialisation
int* ptr2{ new int{ 6 } }; // uniform initialisation
```

## Deleting a single variable

Dynamically allocated variabales must be explicitly deleted to free memory for reuse after we are done with them.
For single variables, use the `delete` operator:

```cpp
// assume ptr has previously been allocated with operator new
delete ptr; // return memory pointed to by ptr to OS
ptr = nullptr; // set ptr to be a null pointer
```

`delete` does not actually delete anything, rather it returns the memory being pointed to back to the OS.
The pointer variable still has the same scope as before and can be assigned a new value like any other variable.

Note that using `delete` on pointers not pointing to dynamically allocated memory can cause undefined behaviours.

Best practice is to set deleted pointers to `nullptr` unless they go out of scope immediately afterwards.
Also, try not to have multiple pointers point at the same piece of dynamic memory to avoid confusion.

### Operator `new` failure

It is possible that the OS may not have any memory to grant the program's request.
By default, if `new` fails, a *bad_alloc* exception is thrown.
If this is not properly handled, the program will terminate (crash) with an unhandled exception error.

A way to use `new` to return a null pointer if memory can't be allocated is to add `std::nothrow` between `new` and the allocation type.

```cpp
int* value{ new (std::nothrow) int }; // value set to nullptr if int allocation fails
```

It is best practice to check all memory requests to ensure they have been successful before using the allocated memory to avoid undefined behaviours.

### Null pointers in dynamic memory allocation

Null pointers can also be useful as they allow the conditional allocation of memory (i.e. if not allocated, allocate) and it is safe to use `delete` on them.

## Memory leaks

Dynamically allocated memory is allocated until explicitly deallocated or the program ends and the OS cleans up (assuming it does that).
However, the pointers used to hold the dynamically allocated memory addresses follow normal scoping rules for local variables and this mismatch can cause problems.

```cpp
void doSomething()
{
    int* ptr{ new int{} };
}
```

In the above example, the function dynamically allocates an integer but doesn't free it using `delete`.
When the function ends, ptr will go out of scope as pointer variables are normal variables.
When ptr is destroyed, there are no more references to the dynamically allocated memory and so the program has "lost" the dynamically allocated memory address.
This means the dynamically allocated integer can't be deleted.

This is called a memory leak.

This causes issues as the program can't return the memory to the OS but the OS considers it to still be in use by the program.

Memory leaks eat up free memory while the program is running and can slow down or crash systems.
The OS is only able to clean up and "reclaim" all leaked memory upon program termination

Another way memory leaks can occur is if a pointer holding the address of dynamically allocated memory is assigned another value.
Double dynamical allocation can also cause memory leaks due to the overwriting of the first allocation.

These can both be fixed by first deleting the pointer before reassigning it.

## Dynamic allocation of arrays

Dynamically allocating arrays allows us to choose an array length at run time.
To do this, use the array forms of `new` and `delete`: `new[]` and `delete[]`.

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a positive integer: ";
    int length{};
    std::cin >> length;

    int* array{ new int[length]{} }; // Note that length doesn't need to be a const here

    std::cout << "You just allocated an array of integers of length " << length << '\n';

    array[0] = 5;

    delete[] array; // deallocates array

    // don't need to set array to nullptr/0 here as going out of scope immediately after 

    return 0;
}
```

The length of dynamically allocated arrays has to be a type convertible to `std::size_t`.
In practice, using an `int` length is fine since it will convert to `std::size_t`.

Because memory is allocated from the heap, dynamically allocated arrays can be quite large in length compared to fixed arrays.

It is important to use ` delete[]` to deallocate dynamically allocated arrays as using the scalar version can result in undefined behaviour.

## Initialising dynamic arrays

To initialise a dynamic array to 0, the syntax is:

```cpp
int* array{ new int[length]{} };
```

Pre C++11, the only way to initialise dynamic arrays was to loop through all elements and assign values explicitly.
Post C++11, dynamic arrays can be initialised with initialiser lists.

```cpp
int fixedArray[5] = { 1, 2, 3, 4, 5 }; // fixed array initialisation
int* array{ new int[5]{ 1, 2, 3, 4, 5 } }; // dynamic array intitialisation post C++11
auto* array{ new int[5]{ 1, 2, 3, 4, 5 } }; // dynamic array intitialisation post C++11, done to prevent writing the type twice
```

## Resizing dynamic arrays

Dynamic allocation allos array length to be set at time of memory allocation.
However, there is no built-in way to resize an array that has already been allocated.
Copying elements over to a new array and deleting the old array is possible but error prone - especially when the element type is a class.

It is best to use `std::vector`, a resizeable array in the standard library, if this capability is needed.


### Comparison to fixed arrays

Fixed arrays can decay to a pointer that points at the first element of the array.
In this form, the length of the fixed array is not known.
Dynamic arrays start as pointers that point to their first elements.
Consequently, they share the same limitation of not knowing their length or size.

Although `new[]` keeps track of how much memory is allocated to a variable, this size/length is not accessible to the programmer.
And so, fixed and dynamic arrays are essentially functionally identical to decayed fixed arrays but the programmer is responsible for deallocating their memory with `delete[]`.


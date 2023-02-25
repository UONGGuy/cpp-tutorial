# Function Pointers

Function pointers are pointers that point to functions (as opposed to variables).
They are primarily useful to store functions in an array or when you need to pass a function to another function.

Consider 
```cpp
int foo() // code for foo starts at memory address __________
{
    return 5,
}
```

`foo` is the function's name/identifier.
Functions, like variables, have their own l-value types and live at an assigned memory address.
When functions are called using the `()` operator, the compiler jumps to the address of the function being called and executes from there.

Sending `foo` to `std::cout` may cause its memory address to be printed.
Not all compilers may convert the function pointer this way.
If you want to force the compiler to print the function address, use `reinterpret_cast<void*>(foo)`.

It is possible to declare a non-const pointer to a function if so desired.

## Pointers to functions

The syntax for creating a non-const function pointer is:
```cpp
// fcnPtr is a pointer to a function taking two double type arguments and returning an int
int (*fcnPtr)(double, double);
```

Without the parentheses around `*fcnPtr`, the compiler would interpret this as a forward declaration for a function called fcnPtr taking no parameters and returning a pointer to an integer.

To make a const function pointer, the syntax is:
```cpp
int (*const fcnPtr)();
```

## Assigning a function to a function pointer

Function pointers can be initialised with a function.
```cpp
int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

int main()
{
    int (*fcnPtr)(){ &foo }; // fcnPtr points to foo

    fcnPtr = &goo; // fcnPtr points to goo
    // fcnPtr = goo() is incorrect

    return 0;
}
```

Similar to pointers to variables, `&foo` can be used to get a function pointer to foo.

C++ will implicity convert functions to function pointers if needed (i.e. don't need address-f operator (&) to get function's address).
However, function pointers won't convert to void pointers or vice-versa.

Function pointers can also be initialised or assigned `nullptr` values.

## Calling a function using a function pointer

Functions can be called from function pointers either by explicit dereference or implicit dereference.

```
int foo(int x)
{
    return x;
}

int main()
{
    int (*fcnPtr)(int){ &foo };

    (*fcnPtr)(5); // explicit dereference: call foo(5) through fcnPtr

    fcnPtr(6); // implicit dereference: call foo(6) through fcnPtr

    return 0;
}
```

Some older compilers don't support implicit dereferencing, but all modern compilers should.

Note that default paramters don't work for function called through function pointers.
This is because default parameters are resolved at compile-time but function pointers are resolved at run-time.

Because function pointers can be set to nullptr, it is a good idea to assert or conditionally test if function pointers are null pointers before calling them.

## Passing functions as arguments to other functions

Function pointers are most useful for passing functions as arguments for other functions.
Functions used as arguments to other functions are sometimes called callback functions.

An example would be the ability to change how a sorting algorithm compares integers (e.g. ascending/descending sort).
Here is code for a selection sort with this additional functionality provided through function pointers.
```cpp
#include <utility> // std::swap

// Sorting function. User-defined comparison is last parameter.
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
// Or alternatively, void selectionSort(int* array, int size, bool comparisonFcn(int, int))
// this form only works for function parameters though
{
    // Iterate through array elements
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is index of smallest/largest element encountered so far
        int bestIndex{ startIndex };

        // Seek smallest/largest element left in array from startIndex + 1

        for (int currentIndex{ startIndex + 1 }; currentIndex < (size - 1); ++currentIndex)
        {
            // If current element is smaller/larger than previously found smallest/largest
            if (comparisonFcn(array[bestIndex], array[currentIndex]))
            {
                // New smallest/largest index for this iteration
                bestIndex = currentIndex;
            }
        }

        // Swap start element with smallest/largest found of remaining elements
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// Comparison function for ascending sort
bool ascending(int x, int y)
{
        return x > y;
}

// Comparison function for descending sort
bool descending(int x, int y)
{
        return x < y;
}

// call selectionSort(array, size, ascending) 
// or selectionSort(array, size, descending)
```

### Providing default functions

It is possible to assign a default funtion to an argument for a function pointer.
However, you must ensure the default function is declared prior to this point else the compiler won't know what the identifier refers to.
```cpp
// Choose ascending sort as default
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);
```

### Using type aliases for clarity

Type aliases can be used to make pointers to functions look more like regular variables and thus easier to read and understand.
```cpp
using ValidateFunction = bool(*)(int, int);
// type alias for a pointer to a function taking two ints, returning a bool

bool validate(int x, int y, ValidateFunction pfcn);
// equivalent to: bool validate(int x, int y, bool (*fcnPtr)(int, int));
```

## Using std::function

Function pointers can also be defined and stored using `std::function` which belongs to the `<functional>` header.
Syntax to define a function pointer is:
```
#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> fcn);
// std::function method taking two ints, returning a bool
```

If there are no parameters, the parentheses can be left empty.

We can also use this in conjunction with type aliases.
```cpp
using ValidateFunction = std::function<bool(int, int)>;
```

Note `std::function` only allows the function to be called via implicit dereference (e.g. `fcnPtr()`, not explicit dereference `(*fcnPtr)()).

Since C++17, CTAD can deduce the template parameters of a `std::function` from an initialiser.
```cpp
#include <functional>

int foo()
{
    return 5;
}

int main()
{
    std::function<int()> fcnPtr{ &foo };

    std::function fcnPtr2{ &foo }; // CTAD parameter deduction

    return 0;
}
```

CTAD does not work for type alias definitions as no intiialiser is provided.

Best practice is to use `std::function` due to the native syntax not being easy to decipher.

### Type inference for function pointers

`auto` can be used to infer function pointer types.
```cpp
auto fcnPtr{ &foo };
```

The downside is that the details about the function's parameter types and return type are hidden so it is easier to make mistakes when calling the function.



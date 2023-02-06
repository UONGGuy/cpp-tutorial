# Introduction to std::array

`std::array` excists in the `<array>` header as a means of making array management easier.

It provides fixed array functionality that won't decay when passed into a function.

Although there can be a bit more hassle with defining size and type and indexig type mismatches, it is recommended to use `std::array` over built-in fixed arrays for any non-trivial array use.

An example of declararing a `std::array` is as follows:

```cpp
#include <array>

std::array<int, 3> myArray; //declare an int array length 3
```

Similar to fixed arrays, the length of a `std::array` must be known at compile time.

## Initialising a std::array

`std::array` can be initialised using an initialiser list or list initialisation:

```cpp
std::array<int, 3> myArray = { 1, 2, 3 }; // initialiser list
std::array<int, 3> myArray2{ 1, 2, 3 }; // list initialisation
```

For pre C++17 compilers, it is not possible to omit array length when providing an initialiser.
However, since C++17, both size and type can be omitted together (but not one or the other) only if the array is explicityl initialised.
The compiler deduces both type an length itself.
Since C++20, it is possible to specify type but omit array length.

### std::to\_array

To create an array with a specific type and deduced size, use the `std::to_array` function:

```cpp
auto myArray1{ std::to_array<int, 5>({ 1, 2, 3, 4, 5 }) }; // specify type and size
auto myArray2{ std::to_array<int>({ 1, 2, 3, 4, 5 }) }; // specify type, deduce size
auto myArray3{ std::to_array({ 1, 2, 3, 4, 5 }) }; // deduce type and size
```

However, `std::to_array` is more expensive than creating a `std::array` directly due to copying all elements from a C-style array to a `std::array`.
As such, it is recommended to avoid `std::to_array` when the array is created many times (e.g. in a loop).

## Accessing values

Values in a `std::array` can be accesed using the subscript operator ([]) as they would be if in a fixed array.
They can also be accessed using the `at()` function that does runtime bounds checking, unlike the subscript operator.
If an out of bounds call occurs, an exception of type `std::out_of_range` is thrown.
Although `at()` is slower that `operator[]`, it is safer.

```cpp
std::array myArray{ 1, 2, 3, 4, 5 };
myArray.at(1) = 6 // same as myArray[1] = 6
myArray.at(9) = 1; // invalid element, throws runtime error
```

## Size and sorting

`size()` can be used to retrive the length of the `std::array`.

```cpp
std::array myArray{ 1, 2, 3, 4, 5 };
std::cout << "Length: " << myArray.size() << '\n'; // prints 5
```

`size()` will work if called from withing a function since `std::array` does not decay to a pointer when passed to a function.

Because the length is always known, `std::array` can be used in for-each loops and can also be sorted using `std::sort` in the `<algorithm>` header.

## Passing std::array to functions

Because element type and array length are part of the type information, they have to be specified when using a `std::array` as a function parameter.

To increase the generality of functions, we can create template functions that parameterise all or part of the type information.

```cpp
#include <array>
#include <cstddef>
#include <iostream>

template <typename T, std::size_t size> // parameterise type and size
void printArray(const std::array<T, size>& myArray)
{
    for (auto element : myArray)
        std::cout << element << ' ';
    std::cout << '\n';
}

int main()
{
    std::array myArray1{ 1, 2, 3, 4, 5 };
    printArray(myArray1);

    std::array myArray2{ 1.2, 3.4, 5.6, 7.8, 9.0 };
    printArray(myArray2);

    return 0;
}
```

Remeber to pass `std::array` by reference or `const` reference to avoid making expensive copies of the `std::array`.

## Manually indexing std::array in for loops

When writing the init-statement for loops iterating through `std::array`, it is importatnt to note that although both `size()` and `operator[]` use type `size_type`, these are both unsigned integral types.
This means an `int` type counter/index variable, which is a signed int, will not match if we have a statement like:
```cpp
for (int i{ 0 }; i < myArray.size(); ++i)
```

`size_type` is not a global type like `int` or `std::size_t`, but is defined inside `std::array`.
This means when we want to use `size_type`, we need to prefix it with the full array type (e.g. `std::array<int, 5>::size_type`).
Fortunately, `std::array::size_type` is an alias for `std::size_t` so we can use that instead.

Be wary that unsigned integers wrap around when their limits are reached and so decrementing an index that is 0 already will cause it to wrap-around to the maximum value.
The solution is to use the postfix operator rather than the prefix operator of `++` or `--` depending on the loop.

The best solution is to try and use for-each loops instead of manually indexing loops.

## Array of struct

Every type that can be used in a regular array can also be used in a `std::array`.
This includes structs.

It is important to note that a `std::array` is defined as a struct containing a C-style array member so an extra set of braces is required if we want to use list initialisation.

```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    std::array<House, 3> houses{ // initialiser for houses
        { // extra set of braces to initialise C-style array member inside std::array struct
            { 13, 4, 30 }, // initialiser for element 0
            { 14, 3, 10 }, // initialiser for element 1
            { 15, 3, 40 }, // initialiser for element 2
        }
};
```

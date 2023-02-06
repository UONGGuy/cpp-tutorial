# Introduction to std::vector

`std::vector` provides dynamic array functionality that handles its own memory management.
This allows arrays to be created that have lengths set at run time without needing to explicitly allocate and deallocate memory with `new` and `delete`.`std::vector` lives in the `<vector>` header.

An example of declaring a `std::vector`:

```cpp
#include <vector>

//no need to specify length at declaration
std::vector<int> v;
std::vector<int> v2 = { 1, 2, 3 }; // pre C++11 initialiser list
std::vector<int> v3{ 1, 2, 3 }; // uniform initialisation
std::vector v4{ 1, 2, 3 }; // since C++17 can omit type (is deduced)
```

In both initialised and uninitialised cases, the array length does not need to be included at compile time as `std::vector` will dynamically allocate memory for its contents as requested.
Vectors will not resize automatically if an element that is out of bounds is requested.
They will, however, resize if assigned new values through an initialiser list:

```cpp
v = { 0, 1, 2, 3, 4 }; // vector length now 5
v = { 1, 2, 3 }; // vector length now 3
```

Elements can be accessed using the `[]` operator or `at()` function as they are for `std::array`.

When vectors go out of scope, they automatically deallocate the memory the control if necessary, preventing memory leaks.

Vectors also remember their length so we can use the `size()` function to access this.
Note this returnes a value which is an unsigned integer in the same manner as `std::array`.

## Resizing vectors

Resizing a `std::vector` using the `resize()` function is straightforward:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector v{ 0, 1, 2 };
    v.resize(5); // set size to 5

    std::cout << "Length : " << v.size() << '\n';

    for (int i : v)
        std::cout << i << ' ';
        // prints 0 1 2 0 0

    std::cout << '\n';

    return 0;
}
```

When resizing an array, existing elements are preserved and new elements are zero-initialised.
Vectors can also be resized to smaller.

Note that resizing is computationally expensive so the number of times it is done should be minimised.

To specify a vector of given length, use parenthesis initialisation:

```cpp
std::vector<int> v(5); // vector of length 5, elements all zero initialised
```

## Compacting bools

There is an implementation for `std::vector` of type bool that compacts 8 booleans into a byte.
Note that this doesn't change how `std::vector` is used.



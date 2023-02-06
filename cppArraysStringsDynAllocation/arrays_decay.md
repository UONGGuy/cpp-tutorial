# Array decay

When a fixed array is used in an expression, it will decay (be implicitly converted) to a pointer that points at the first element of the array.

```cpp
#include <iostream>

int main()
{
    int array[5]{ 9, 7, 5, 3, 1 };

    // print address of array's first element
    std::cout << "Element 0 has address: " << &array[0] << '\n';
    
    // print value of pointer array decays to
    std::cout << "The array decays to pointer holding address: " << array << '\n';

    return 0;
}
```

It is important to distinguish that an array and a pointer to the array are NOT identical.

In the exaple above, the array is type "int[5]" and its "value" is the array elements themselves.
A pointer to the array would be of type "int\*" and its value would be the address of the first element of the address.

All elements of the array can still be accessed through the pointer, but information derived from the array's type (e.g. array length) can't be accessed from the pointer.

However, this effectively allows fixed arrays and pointers to be treated similarly in most cases.

We can dereference array to get the value of first element but note we don't actually dereference the array itself, but the array of type "int[5]" gets implicitly converted to a pointer of type "int\*" which is then dereferenced to get the value at the memory address of the pointer (which is the same).

We can also assign a pointer to point at the array.

## Differences between pointers and fixed arrays

There are a few cases that help distinguish between the typing of pointers and fixed arrays.

The main one is that when using the `sizeof()` operator, fixed arrays return the size of the entire array (array length * element size) but for a pointer, only the size of the pointer (in bytes) is returned.

Another important one comes when using the address-of operator (&).
Taking the address of a pointer gives the memory address of the pointer variable.
Taking the address of a fixed array returns a pointer to the entire array.
Although this pointer also points to the first element of the array, the type information is different.

```cpp
#include <iostream>

int main()
{
    int array[5] { 9, 7, 5, 3, 1 }:
    std::cout << array << '\n'; // type int[5], prints 009DF9D4
    std::cout << &array << '\n'; // type int(*)[5], prints 009DF9D4

    int* ptr{ array };
    std::cout << ptr << '\n'; // type int*, prints 009DF9D4
    std::cout << &ptr << '\n'; // type int**, prints 009DF9C8

    return 0;
}
```

## Passing fixed arrays to functions

It is noted in arrays\_intro.md that we pass arrays as const in functions to avoid expensive copying costs.

Due to array decay, when a fixed array is passed as an argument to a function, the pointer is passed to the function.

```cpp
#include <iostream>

void printSize(int* array)
{
    // array treated as pointer
    std:: << sizeof(array) < '\n'; // prints size of pointer, not array
}

int main()
{
    int array[]{ 1, 2, 3, 4, 5, 6, 7, 8 };
    std::cout << sizeof(array) << '\n'; // prints sizeof(int) * array length

    printSize(array); // array argument decays to pointer here, returns size(of) int

    return 0;
}
```

Decay happens even if the function parameter is declared as a fixed array as C++ implicity converts it to a pointer.

This means the following function declarations are identical:
```cpp
void printSize(int array[]);
void printSize(int* array);
```

Often you'll end up having to pass array size as a separate parameter since the pointer doesn't tell you how large the array is.

The fact arrays decay when passed to functions explains why changing an array in a function changes the actual array argument passed in.

Arrays that are parts of structs or classes do not decay when the whole struct or class is passed to a function.
This is a useful way to prevent decay if we desire.

It is recommended to use pointer syntax to make clear the parameter will be treated as a pointer, not a fixed array.

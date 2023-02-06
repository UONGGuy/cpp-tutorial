# Arrays

Arrays are aggregate an aggregate data type that allows us to access many variables of the same type through a single identifier.
The variables that make up an array are called elements.

There are two main varieties of arrays: fixed arrays and dynamic arrays.
Fixed arrays have memory allocated at compile time and cannot have their array length changed.
Dynamic arrays can have their lengths changed but are more complicated to instantiate.

## Array variable declaration

Fixed arrays are declared using square brackets`[]` with the array length (how many elements to contain) specified within them.

```cpp
int array[20]{}; // allocate 20 int variables in a fixed array
```

With fixed array declarations, the length of the array must be a compile-time constant as it needs to be known at compile time.
It is also possible to declare a fixed array without a length where the initiliser list used sets length instead.

### Initialising arrays

Array elements are treated like normal variables and are not initialised when created.
One way to initialise an array is to initialise each element individually.

For fixed arrays, it is more convenient to use an initialiser list instead.
If there are less initialisers in the list than elements in the array, the remaining elements are zero initialised.

### Array length

`std::size()` from the `<iterator>` header can be used to determine an array's length.
However, this does not work for arrays that have been passed to functions due to the way C++ passes arrays to functions.

`std::size()` also works for other objects such as `std::array` and `std::vector`.

Note that it returns an unsigned value which may require you to cast the result or use `std::ssize()` (C++20) if a signed value is desired.

If the `sizeof()` is used on an array, it returns the total size of the array (array length times element size).

This means array length can be deduced by dividing its total size by the size of an array element:

```cpp
sizeof(array) / sizeof(array[0])
```

Note this menhod only works for a fixed-length array.
Be wary that if `sizeof()` is used on an array passed to a function, it returns the size of a pointer instead.

## Array elements and subscripting

To access individual elements of an array, we call the array name with the subscript operator `[]` and the subscript (or index) of the element (i.e. where in the array it is).

```cpp
int main()
{
    int array[5];
    array[0] = 1; // first element, index 0, value 1
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5; // last element, index 4, value 5
    
    return 0;
}
```

Arrays are 0-indexed meaning for an array of length N, the first element has an index 0 and the last has an index of N-1.
This is the array's range.

C++ does not check if indices are valid for array length so it is possible to access an element outside the array's range.
The value is inserted where the element would have been if it existed but this can lead to undefined behaviour so should be avoided.
This is the same with negative indexes.

Note that array subscripts must always be an integal type.

For better documentation, enums can be used with arrays to index them and make it easier to understand what each index of the array corresponds to.
The can also be used to set the array length too.
Note that this is due to the implicit conversion property enums haveso (i.e. enum classes are less conveninent to use as they need explicit conversion).

## Array data types

Arrays can be made from any data type.
This includes structs and even other arrays.

```cpp
struct Rectangle
{
    int length{};
    int width{};
};

int main()
{
    Rectangle rects[5]{}; // declares an array of 5 Rectangle
    
    rects[0].length = 24 // sets first element of array to have length 24

    return 0;
}
```

## Passing arrays to functions

Passing an array to a function causes the actual array to be passed rather than a copy of it (due to large copying cost).
This means functions can diretly change the value of array elements if not careful.

To ensure functions don't modify array elements, we can make the array `const` in the function argument.

## Loops and arrays

Loops are a good solution to improve the readability and maintenance of code that needs to cycle through arrays or perform calculations on each array element.

They are typically used to:
- Calculate a value (e.g. average, total value)
- Search for a value (e.g. highest/lowest value)
- Reorganise the array (e.g. ascending/descending order)

Sorting arrays are more difficult as they usually involve nested loops.

It is important to ensure the loop range matches with array's range to avoid indexing mismatches that can lead to errors.

# Pointers to pointers and dynamic multidimensional arrays

## Pointers to pointers

If pointer A points to pointer B, then pointer A holds the address of pointer B.

Pointers to pointers are decared using two asterisks.

```cpp
int* ptr; // pointer to an int
int** ptrptr; // pointer to a pointer to an int
```

Pointers to pointers work like normal pointers in that they can be dereferenced to access the value pointed at.
Since this is a pointer, we can dereference once more to obtain the underlying value.

You cannot set a pointer to a pointer directly to a value.

### Arrays of pointers

A most common use for pointers to pointers is to dynamically allocate an array of pointers.

```cpp
int** array{ new int*[10] }; // allocate an array of 10 int pointers
```

This works like a standard dynamically allocated array except the array elements are of type "pointer to integer" instead of integer.

### Multi-dimensional dynamic arrays

Another common use is to facilitate dynamically allocated multidimensional arrays.

There are two ways to dynamically allocate a 2D array.
If the rightmost array dimension is `constexpr`, we can do this:
```cpp
int x{ 7 }; // non-const
int (*array)[5]{ new int[x][5] }; // rightmost dim must be constexpr
```

If it isn't, then we first allocate an array of pointers, iterate through it, and allocate a dynamic array for each array element.
That is, a dynamic 2D array is a dynamic 1D array of dynamic 1D arrays.
```cpp
int** array{ new int*[10] }; // array of 10 int pointers - these are rows

for (int count{ 0 }; count < 10; ++count)
    array[count] = new int[5]; // these are columns

array[9][4] = 3; // same as (array[9])[4] = 3; access array as usual
```

Because each array column is dynamically allocated independently, it is possible to make dynamically allocated 2D arrays that are not rectangular.

Deallocating a dynamic 2D array with this method also requires a loop:
```cpp
for (int count{ 0 }; count < 10; ++count)
    delete[] array[count];
delete[] array; // must be done last
```

Note we must delete in the opposite order of creation as we wouldn't be able to access other allocated memory for deallocation otherwise.

Due to the complexity of this, it is often easier to "flatten" 2D arrays of size x-by-y to a 1D array of size x\*y.
Then rows and columns can be simulated by using simple maths.

### Passing a pointer by address

We can pass a pointer to a pointer to a function and use that pointer to change the value of the pointer it points to.

However, if we want a function to modify what a pointer argument points to, it is generally better done using a reference to a pointer instead.

### Pointer to a pointer to a pointer to...

It is possible to declare a pointer to a pointer to a pointer (and so on):
```cpp
int*** ptrx3;
```

This can be used to dynamically allocate a 3D array but would require a lop in a loop and gets much more complicated.

However, these aren't used very frequently.

It is recommended to avoid using pointers to pointers unless no other options are available due to the multitude of things that can go wrong.

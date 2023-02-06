# Multidimensional Arrays

Elements of arrays can be of any data type - this includes other arrays.
A multidimesional array refer to an array of arrays.

```cpp
int array[3][4]; // is a 2D array: 3-element array of 5-element arrays
```

The number of subscripts corresponds to the number of dimensions in the array.

## Initialising 2D arrays

It is best to use nested braces with each set of numbers representing a row when initialising 2D arrays.

```cpp
int array[3][5]
{
    { 1, 2, 3, 4, 5 }, // row 0
    { 6, 7, 9, 9, 10 }, // row 1
    { 11, 12, 13, 14, 15 } // row 2
};
```

Any missing initialisers will be replaced with zeros.

2D arrays with initialiser lists can only have the first subscript unspecified (e.g. `int[][5]`).

## Accessing 2D array elements

To access all elements, we require two loops: one for the row number, one for the column number.
2D arrays are typically accessed row-by-row and so the row index is usually the outer loop.

```cpp
for (int row{ 0 }; row < numRows; ++row) // iterate through rows in array
{
    for (int col{ 0 }; col < numCols; ++col) // iterate through columns numbers of elements in the row
    {
        std::cout << array[row][col];
    }
}
```

`for-each` loops can also be used with multidimensional arrays.

## Higher dimension multidimensional arrays

Per additional dimension, we add an additional subscript and access them similarly to 2D arrays:

```cpp
int array[5][4][3]; // 3D array

std::cout << array[3][1][2]; // print array from index 3 of dim-1, index 1 from dim-2, index 2 from dim-3
```


# Sorting arrays

Sorting is an important organisational concept that can speed up processes immensely.
The issue is that sorting algorithms can be relatively expensive and so may not be worth using unles the arra needs to be sesarched multiple times.

## How it works

Generally, pairs of elements are repeatedly compared and then swapped if certain criteria are met.

`std::swap()` from the `<utility>` header allows two elements in an array to be swapped.

Since sorting is so common, function `std::sort()` exists in the `<algorithm>` header and can be used to sort arrays.

## Examples
### Selection sort

Selection sort sorts an array from smallest to largest in the following way:

1. Start at array index 0 and search for the smallest value in all array indices greater than the starting index.
2. Swap the smallest value in the array with the value at index 0.
3. Repeat steps 1 & 2 starting from the next index.

# Introduction to standard library algorithms

There are many common processes such as searching, counting and sorting that are used in programming.
The C++ standard library comes with many functions to reduce the time and effort of implementing and maintaining such routine tasks.
They are pre-tested, efficient, compatible and can support parallelisation.

The functionalities of algorithms generally fall into one of three categories:
- Inspectors: Used to view but not modify data in a container (e.g. searching, counting)
- Mutators: Used to modify data in a container (e.g. sorting, shuffling)
- Facilitators: Used to generate a result based on values of data members (e.g. multiplying values, determining what order pairs should be sorted in).

These algorithms live in the algorithms library and make use of iterators.

Where possible, you should favour functions from the algorithms library over writing your own functionality to do the same thing.

## std::find and std::find\_if

`std::find` seraches for the first occurrence of a value in a container.
It takes 3 parameters:
1. Iterator to the starting element of the sequence
2. Iterator to the ending element of the sequence
3. Value to search for

It returns an iterator pointing to the element if found or to the end of the container if not found.

If we are interested to see if there is a value in a container that matches some condition, we can use `std::find_if`.
It works similarly to `std::find` but takes a callable object (e.g. function pointer, a lambda) instead of a value to search for.
Our called function can be one that returns `true` if a match is found, `false` otherwise.

## std::count and std::count\_if

`std::count` can be used to search for all occurrences of an element.
`std::count_if` can be used to search for all occurrences of an element fulfilling a condition.

Syntax is similar to that for `std::find` and `std::find_if`.

## std::sort

We can use `std::sort` to sort an array according to a custom rule (if desired).
It takes 3 parameters, similar to `std::find`:
1. Iterator to the starting element of the sequence
2. Iterator to the ending element of the sequence
3. (Optional - default: sort in ascending order) Custom function by which to compare elements (Function must have 2 arguments for element comparison)

## std::for\_each

`std::for_each` takes a list input and applies a custom function to each element.
It has the same parameters as `std::find_if`

Although it can seem a bit redundant as for-each loops ecist, it improves the clarity of code and we can designate different start/end points for applying our custom function.

It can also be parallelised.

## Order of execution

Most algorithms in the algorithms library do not guarantee a particular order of execution so it is important to ensure any functions you pass in do not assume a particular ordering.

Some algorithms that do guarantee sequential execution include: `std::for_each`, `std::copy`, `std::copy_backwards`, `std::move`, and `std::move_backward`.

## Ranges in C++20

From C++20, the inclusion of ranges means the array object itself can simply be passed into algorithms instead of having to explicitly pass `array.begin()` and `array.end()`.



# Introduction to iterators

Iterating through data structures is common in program.
So far, we have covered doing this with loops and an index (for loops, while loops), with pointers and pointer arithmetic, and with for-each loops.

However, not all containers (e.g. structures holding data) provide direct access to elements, nor are elements always consecutive in memory.

Iterators are objects designed to traverse through a container and provide access to each element along the way.
This allows other algorithms such as `std::sort` to be used as well.

Containers may provide different kinds of iterators.
Once the appropriate type of iterator is created, the programmer doesn't have to worry about what kind of traversal is being done or how data is being stored.

C++ iterators typically use the same interface for traversal (`operator++` to move to next element) and access (`operator*` to access current element).

## Pointers as iterators

We can use a pointer as an iterator by using pointer arithmetic to traverse data stored sequentially in memory.

Pointers without pointer arithmetic can also be used to iterate through some non-sequential structures.
In a linked list, each element is connected to the prior element by a pointer and the list can be iterated through by following the chain of pointers.

## Standard library iterators

The standard library offers direct support for iteration with the `begin()` and `end()` functions that mean we don't have to manually calculate the begin and end points of our container.
We can also use `std::begin` and `std::end` from the `<iterator>` header to the same effect.

```cpp
#include <array>
#include <iostream>
//#include <iterator>

int main()
{
    std::array array{ 1, 2, 3 };

    auto begin{ array.begin() }; // or std::begin(array)
    auto end{ array.end() }; // or std::end(array)

    for (auto p{ begin }; p != end; ++p)
    {
        std::cout << *p << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

## For-each loops

All types that have both `begin()` and `end()` member functions/can be used with `std::begin()` and `std::end()` are usable in for-each loops.

This is because for-each loops call these and iterate through them in the background.

This means we can use for-each loops with C-style fixed arrays but not dynamic arrays as they have no `std::end` function (type information doesn't contain array length).

It is possible to add functions to types to be used with for-each loops.

## Iterator invalidation (dangling iterators)

Iterators can be left "dangling" if the elements being iterated over change address or are destroyed.
Accessing invalidated iterators produces undefined behaviour.

Some operations that modify containers (e.g. adding an element to a `std::vector`) can have the side effect of causing elements in the container to change addresses, invalidating existing operators.



# For-each loops

For-each loops (also called range-based for-loops) are simpler and safer ways to iterate through all elements in an array or other list-type structures.
They should be preferred over standard for loops when they can be used.

The syntax looks like the following:
```cpp
for (element_declaration : array)
    statement;
```

It is important to ensure the element declaration is the same type as the array elements to avoid type conversions.
Most of the time, `auto` is used to detect element type.

```cpp
#include <iostream>

int main()
{
    constexpr int array[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (auto number : array)
    {
        std::cout << number << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

Note that the variable "number" is not an index array here, but the assigned value of the array element for the current loop iteration.

Because element declarations are declared by value, every time such a declaration is made, the array element is copied and not referred to which can be expensive.

Fortunately, for-each loops can also take (const) reference element declarations too.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string array[]{ "peter" , "likes", "frozen", "yoghurt" };
    
    for (auto& element : array ) // use const auto& if read-only
    {
        std::cout << element << ' ';
    }
    
    return 0;
}
```

Note that an array has to have size information for this to work.
An array that has decayed to a pointer cannot be used in a for-each loop.

### With other structures

For-each loops can work with many list-like structures including
- Vectors (e.g. `std::vector`)
- Linked lists
- Trees
- Maps

### With pointers to arrays

For-each loops can't be used with pointers to arrays because the size information is needed and this is not known by pointers.

Similarly, dynamic arrays won't work with for-each loops for this reason.

### Array indexes

For-each loops do not provide direct methods of getting the array index of the current element as some of the structures they work with are not directly indexable.

Since C++20, they can be used with an init-statement like in normal for loops.
These can be used to create manual index counters without polluting the function in which the for loops is placed.

The syntax is:

```cpp
for (init-statement; element_declaration : array)
    statement;
```

An example init-statement which creates a manual index would be

```cpp
int i{ 0 }
```

and only gets executed once the loop starts and would only increase in increment if made to do so in the statement (e.g. `++i`).

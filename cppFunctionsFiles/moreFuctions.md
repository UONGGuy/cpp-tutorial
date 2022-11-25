# Functions

Functions give the user a way of performing a routine task in a concise and straightforward manner that reduces the amount of repeated code needed.

There are two ways to write code to perform a task:
1. Create a function (and sub-functions if necessary)
2. Write code "inline"

Writing functions is standard and comes with many advantages:
- Readability, easy to understand purpose in program
- Easy to implement
- Easy to update
- Easy to reuse

However, the main downside is that calling functions can have large overhead costs due to the program having to ump between different code blocks.

For larger/more complex functions, this cost is insignificant compared to overall time taken to run the fuction.
For smaller functions, this cost can sometimes be quite significant compared to writing the same code in-place.


## Inline expansion

To avoid overhead cost, we can use **inline expansion**: replacing a function call with the code in its defintion.

An inline function is one whose function call can be expanded.

```cpp
#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n'; // using a function
    std::cout << ((5 < 6) ? 5 : 6) << '\n'; // using inline code

    return 0;
}
```

Inline expansion is best used for simple, short functions and is especially useful to replace function calls in loops.

The `inline` keyword works to define a function type but is outdated for modern use and so should be avoided.

## Constexpr and consteval functions

Remembering that we can use `constexpr` to create compile-time (symbolic) onstants, it is also possible to evaluate some functions at compile-time which improves performance.

The conditions for this are that the function:
- Has a constexpr return type
- Only take constexpr arguments (variables or literals)
- Does not call any non-constexpr functions

```cpp
#include <iostream>

constexpr int greater(int x, int y) // constexpr function
{
    return (x > y) ? x : y;
}

int main()
{
    constexpr int x { 5 };
    constexpr int y { 6 };

    constexpr int g { greater(x, y) }; // evaluated at compile-time, replaced with return value 6

    std::cout << g << "is greater\n";

    return 0;
}
```

Due to being evaluated at compile-time, the compiler must be able to see the full definition at all points where it is called.
constexpr functions are implicity inline to avoid needing to be called into every file they are called in.
As such, they are often defined in header files.

constexpr functions can also be evaluated at runtime if it is not possible for compile-time evaluation (e.g. if an input is not constepxr).

It is possible to check for compile-time evaluation usin `std::is_constant_evaluated()` which returns a bool that can be used for testing.

## Immediate functions

It is possible to force compile-time evaluation as the preference by specifying the return value is where a constant expression is required (see above example) or by using the `consteval` keyword.

`consteval` forces compile-time evaluation but is only available at C++20 and beyond.
These functions are caled immediate functions and will return an error if compile-time evaluation is not possible.

If we want the flexibility of a constexpr function but a preference for compile-time evaluation, we can write a helper function as such:

```cpp
#include <iostream>

consteval auto compileTime(auto value) // helper function
{
    return value;
}

constexpr int greater(int x, int y) // constexpr function
{
    return (x > y>) ? x : y;
}

int main()
{
    std::cout << greater(5, 6) << '\n'; // compiler chooses evaluation at compile-time or runtime
    std::cout << compileTime(greater(5, 6)) << '\n'; // executes at compile-time
    
    int x { 5 };
    std::cout << greater(x, 6) << '\n'; // can still call constexpr function at runtime

    return 0;
}
```


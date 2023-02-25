# Recursive functions

These are functions which call themselves infinitely or until a recursive termination condition is met.
Most recursive terminations involve `if` statements.
```cpp
// Function to return the value of n! using a recursive function
double factorial(double n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}
```

When writing recursive functions, it is important to remember that functions are pushed to the call stack and popped off in the LIFO order as this affects the order of statement execution.
Side effects of operators must also be taken account of (e.g. `operator--`).

## Recursive algorithms

Typically, recursive functions are used to solve problems by looking at relational subsets of that make up the solution.
Often, some inputs lead to trivial outputs.
These base cases usually act as termination conditions for the algorithm.

### Fibonacci numbers

This is one of the more famous examples of a recursive algorithm.

Mathematically, the n-th Fibonacci number is defined as:
---
F(n) =  0 if n = 0
        1 if n = 1
        f(n - 1) + f(n - 2) if n > 1
---

A simple (but inefficient) recursive function to return the n-th Fibonacci number is:
```cpp
int fibonacci(int count)
{
    if (count == 0)
        return 0;
    if (count == 1)
        return 1;
    return fibonacci(count - 1) + fibonacci(count - 2);
}
```

## Memoisation algorithms

Memoisation is a technique used to cache the results of expensive function calls so th result can be returned when the same input occurs again.

An example of this applied to the Fibonacci recursive algorithm:
```cpp
#include <vector>

int fibonacci(int count)
{
    // Use setatic std::vector to cache calculated results
    static std::vector results{ 0, 1 };

    // If count already seen, used cached result
    if (count < static_cast<int>(std::size(results)))
        return results[count];

    // Otherwise calc new result and store it
    results.push(back(fibonacci(count - 1) + fibonacci(count - 2));
    return results[count];
}
```

## Recursion vs iteration

Many tasks can be done by both recursion and iteration.
However, there are some cases where the recursive version is easier to read and write (e.g. Fibonacci).

It should be noted though that iterative functions are almost always more efficient than their recursive counterparts due to not havving the overhead cost of pushing and poping stack frames.

Recursive functions tend to be a good choice when:
- The recursive code is much simpler to implement
- The recursion depth can be limited
- The it3erative version requires managing a stack of data
- It isn't a performance-critical code section



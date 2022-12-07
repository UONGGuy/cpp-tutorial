# Control flow 

This refers to the order in which programs execute actions.

If a program runs in the same order as statements are written, it is a straight-line program.

When control flow statements are used to change the point of execution, it is known as branching.

## Control flow statement categories

| Category | Meaning |
| ----------- | ----------- |
| Conditional statements | Code block executes only if a condition is met|
| Jumps | Tells CPU to execute code located at a different location |
| Function calls | Jumps to a different location and then returns |
| Loops | Tells program to repeatedly execute code within the block until some condition is met |
| Halts | Tell program to quit running |
| Exceptions | Flow control structure for error handling |

## 'if' and 'else' statements

Conditional statements that execute the following code block if the given condition is met and a different code block if not (else).

```cpp
if (condition)
{
    // block to execute if condition true
}
else // optional
{
    // block to execute if condition false
}
```

Single statements to be executed if conditions are met don't have to be put in blocks, but it is useful if additional statements are added later.

Remember that variables defined in blocks have block scope and will be destroyed at the end of the block.

`else` and `if` can be combined to create the `else if` statement that follows an initial `if` statment and executes if that proves false but condition (defined after the `else if`) holds.

## 'switch' statements

An alternative conditional statement that allows various cases to be tested.
Can be used to replace lengthy if-else chain statements.
Cannot, however, be used with inequalities - only accepts integral types for cases.

```cpp
switch (x) // condition inside parentheses
{
    case 1: // x == 1
        std::cout << "One";
        return;
    case 2: // x == 2
        std::cout << "Two";
        return;
    case 3: // x == 3
        std::cout << "Three";
        return;
    default: // if the cases are not met. Is optional and should be placed last in the switch block
        std::cout << "Unknown";
        return;
}
``` 

One restriction is that the `switch` condition must evaluate to an integral type.
If the condition does not match any case labels (and there is no default), no cases are executed.
Another is that variables can be declared or defined in switch blocks, but not initialised.
Defining variables should be done in case statement blocks.

Note that without the use of `return` or `break` statements, the program would simply move execute the next case. This attribute is called `[[fallthrough]]`.

Noting this attribute where there are null statements in code can be useful in indicating that fallthrough is intentional.

It can be useful if you want the same action to occur if any of a set of conditions are met.

## 'break' statements

`break` allows us to exit the current block of code for a conditional statement and continue the program from the end of the block.

## 'continue' statements

`continue` allows the current iteration of a loop to be ended without terminating the entire loop.
It causes the current point of execution to jump to the bottom of the current loop.

## 'goto' statements

These are unconditional jumps to a different location of code.
To do this, a `goto statement` and `statement label` are defined which tell the program when it should jump and where to.
These functionalities have function scope - i.e. the label is visible throughout the function even before its point of declaration - and both must appear in the same function.

```cpp
#include <iostream>

int main()
{
    int x {};
tryAgain: // statement label - must match goto
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0)
    {
        goto tryAgain; // gotostatement - returns to statement label
    }

    std::cout << x << " is non-negative.\n";
    
    return 0;
}
```

Best practice is to avoid `goto statements` entirely unless the alternatives are significantly worse due to difficulty in understanding program flow when you can jump about in the code arbitrarily.

## 'while' loops

Continually executes code within the block until condition proves false.

```cpp
while (condition)
{
    // code to execute
}
```

Condition is usually incremental (e.g. condition: `count < 10`, `++count` inside loop).

For intentional infinite loops, can declare condition = `true` and use a conditional within the loop to break it.

Loop variables should be signed to avoid the issues that arise with unsigned integers.

It is possible to nest loops inside other loops.

## 'do while' loops

Similar to `while` loops but the contents of the loop is run at least once before the condition is checked.

```cpp
do // code to be run intially, then checked to condition and looped if condition true
{
    // code to execute
}
while (condition);
```

It is less common than while loops but can be useful if prior actions are necessary before condition checking occurs.

## 'for' loops

The most common loop statement in C++.
It has three key parts to it: the init-statement, condition and end-expression.

```cpp
for (init-statement; condition; end-expression)
{
    // code to execute
}
```

The init-statement defines variables used in the loop, the conditiondefines when the loop breaks, and the end-expression modifies the loop variable before reassessment of the condition.

A simple example of printing numbers in a given range:

```cpp
#include <iostream>

int main()
{
    for (int count { 0 }; count < 10; ++count)
    {
        std::cout << count << '\n';
    }
    
    std::cout << "Blast off!\n";

    return 0;
}
```

It is possible to create `for loops` with multiple counters:

```cpp
#include <iostream>

int main()
{
    for (int x { 0 }, y { 0 }; x < 10; ++x, --y)
    {
        std::cout << x << ' ' << y << '\n';
    }

    return 0;
}
```

Nested `for loops` are also possible.

## Halts

Halts terminate the program.
In C++, they are implemented as functions rather than keywords.

Usually, C++ programs implicity terminate by calling `std::exit()` when `main()` ends.

It is possible to call `std::exit()` early to terminate early. This requires the `cstdlib` header.
However, this does not clean up local variables in the current function or up the call stack as it would if done implicitly.

We can specify a manual cleanup functions by specifying them using `std::atexit()` which will execute them in reverse order of listing.

It is also possible to trigger abnormal terminations using `std::abort()` (which also doesn't initiate any clean up).
`std::terminate()` is typically used with `exceptions` but by default calls `std::abort()`.

Best practice is to only use halts if there are no safe ways to return normally from the main function.
Prefer exceptions for handling errors safely if they are enabled.




# Ellipsis

C++ provides a special specifier known as ellipsis (`...`) that allows for a variable number of parameters to be passed to a function.
However, they are rarely used and potentially dangerous so it is recommended they be avoided.

Functions using ellipsis take the form:
```cpp
return_type function_name (argument_list, ...)
```

*argument_list* refers to one or more normal function parameters.
This is necessary as functions using ellipsis must have at least one non-ellipsis parameter.

## Example usage

To use ellipsis, we require the `<cstdarg>` header and functions it contains.

A function calculating the average of many integers is:
```cpp
#include <cstdarg>

double findAverage(int count, ...)
{
    int sum{ 0 };

    // Access ellipsis through a va_list
    std::va_list list;

    // Initialise with va_start
    // First argument is list to initialise
    // Second argument is last non-ellipsis parameter
    va_start(list, count);

    // Loop through all ellipsis values
    for (int arg{ 0 }; arg < count; ++arg)
    {
        // Use va_arg to extract ellipsis values
        // First arg is va_list used
        // Second arg is type of value
        sum += va_arg(list, int);
    }

    // Clean up va_list when done
    va_end(list);

    return static_cast<double>(sum) / count;
}
```

This can take a variable number of parameters.

## Why Ellipsis are dangerous

Despite their seemingly high flexibility, this comes at the cost of type checking the function arguments match the function parameter types.
Because the compiler suspends type checking for ellipsis parameters, it cannot warn you if the arguments called do not make sense.

Ellipsis also don't know how many parameters were passed.
This means the programmer must find a way to keep track of the total number of parameters passed into the ellipsis.

Ways this can be done are:
- Pass a length parameter (can encounter issues if this doesn't match number of passed parameters)
- Use a sentinel value (i.e. a terminating value. This can cause issues if the value doesn't fall outside the set of valid input values and if forgotten in use)
- Use a decoder string (i.e. pass a method of interpreting parameters to the function. This can be a bit cryptic and still cause issues through type mismatches)

## Safer ellipsis use

Best practice is not to use ellipsis at all.

But if they are employed, do not mix expected argument types within them and try using a count parameter or decoder string as part of the argument list if possible.

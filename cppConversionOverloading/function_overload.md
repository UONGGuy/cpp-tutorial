# Function overloading

Function overloading refers to when multiple functions share the same name.
This can be useful in simplifying programs when you want a function to behave in the same way across different data types (e.g. a calculator that add `int` and `double`).
Overloaded functions are valid as long as each identical function (overload) has different parameter types.

```cpp
int add(int x, int y) // int version
{
    return x + y;
}

double add(double x, double y) // double point version
{
    return x + y;
}
```

The compiler tries to match the function call to the correct overload based off the arguments used in the function call (overload resolution).

## Conditions for function overloading

For a program to compile overloaded functions:
- Each overloaded function has to be differentiated from the others.
- Each call to an overloaded function must resolve to an overloaded function.

If neither of these conditions are met, an error will occur.

## Function overload differentiation

Compilers differentiate overloaded functions by their type signature: the  number and type of function paramters, excluding its return type.
Function types that are excluded from differentiation are typedefs, type aliases and the const qualifier on value parameters as they are not distinct types.
These can, however, be used for differentiating member functions.

As long as the number or type of function parameters are distinct, it's possible for the compiler to differentiate between them.
Note though that ellipsis parameters are considered to be unique parameter types and so can be used for differentiation.

## Function overload resolution

Overload resolution is the process of matching function calls to a specific overloaded function.

Usually this is straightforward but in the event the function call doesn't match the parameter types in any of the overloaded functions the compiler follows a set of rules to try and determine the best matched overload to call.

It checks each argument one-by-one and applies different type conversions to check if any overloaded functions are a match.
After all type conversions are applied and checked for matches, there are three possible outcomes:
- No matching functions, moves to check next argument.
- Single matching function, function is considered best match and searching stops.
- Multiple matching functions found, compiler issues ambiguous match compile error.

If the argument matching sequence reaches the end without finding a match, a compile error is generated.

### Argument matching sequence

The argument matching sequence is as follows:
1. Compiler looks for an exact match by checking argument type with overloaded function parameter types. If an exact match is not found intially, trivial conversions are applied. Successful trivial conversions are counted as exact matches.
2. If no exact matches are found, numeric promotion is applied. If successful, function call is resolved.
3. If no matches via numeric promotion are found, numeric conversions are applied to arguments.
4. If no matches via numeric conversion, compiler attempts matches with user-defined conversions (if any).
5. If no matches via user-defined conversion, compiler looks for matching function that uses ellipsis.
6. If no matches by this point, compiler stops search and issues compile error about no matching function.

## Ambiguous matches

If multiple overloads can possibly be used in a given step of the matching process, the compiler issues an error about an ambiguous function call.

```cpp
void print(int x)
{
}

void print(double d)
{
}

int main()
{
    print(5L); // 5L is type long

    return 0;
}
```

In this example, the compiler doesn't find an exact match or a match through numeric promotion.
During checks for numeric conversion, it finds two potential matches but does not know which to use.

Ambiguous matches are compile-time errors and so need to be disambiguated before the program will compile.
Methods for resolution include:
- Defining a new overloaded function with the parameters of the exact type you are trying to call the function with -> exact match.
- Explicitly cast ambiguous arguments to match the type of the function you want to call.
- Use the literal suffix to ensure correct interpretation of literal in the function argument.

## Functions with multiple arguments

For multiple arguments, the compiler applies the matching rules to each argument in turn and chooses the best function based off having a higher number of better matches given each other argument matches just as well as all the other overloads.

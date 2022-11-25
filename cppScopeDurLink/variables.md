# Local variables

Local variables are variables defined inside a function.

They have block scope which means they are in scope from when they are defined until the end of the block they are defined in.

All variable names within a scope must be unique to avoid naming collisions.

Local variables have automatic storage duration (i.e. created at point of definition, destroyed by the end of the block defined in).

Best practice is to define variables in the most limited existing scope - i.e. only within the scope/code blocks that they are used in.
This limits program complexity and reduces the number of active variables at any one time.

# Global varaibles

Global variables are those declared outside a function and can be seen and used everywhere in the file.
Conventionally, they are declared at the top of a file.

They are usually signalled by the prefix "g" or "g\_" in naming conventions.

Their scope is global and so last until the end of the file.
They are considered part of the global namespace and zero-initialised by default.

In general though, non-constant global variables should be avoided.

## Shadowing variables

Since local variables have no linkage, each declaration refers to a unique object.

```cpp
int main()
{
    int x { 2 }; // local variable with no linkage
    
    {
        int x { 3 }; // this identifier x refers to a different object from the previous x
    }

    return 0;
}
```

As is seen in the example, `x` defined in the outer block is hidden when we define `x` in the nested block.
If we did not define `x` in the inner block, then `x` would still refer to the variable defined in the outer block.
There is no way to directly access the shadowed variable from the outer block.

Similar to with local variables, global variables can be shadowed by variables defined with the same name.
However, since global variables are part of the global namespace, the global varaibles can be retrieved by using the scope operatore (::).

Avoid variable shadowing whenver possible.

## Static local variables

`static` is a storage class specifier setting a name's linkage and storage duration (but not its scope).

Using it on a local variable changes its duration from automatic to static: it is now destroyed at the end of the program (rather than the end of the code block).
They are only initialised the first time code is exectued and not on subsequent calls.

It is common to use the "s\_" prefix to denote static local variables.

Static variables have the longevity of global variables whilst having visibility limited to block scope, making them safe to use.

They can also be made const or constexpr.

As a guideline, try to avoid `static` local variables unless the variable never needs to be reset.

## Global varaibles with internal linkage

Global variables can have internal or external linkage.

Internal linkage = can be seen and used within a single file but not accessible from other files.

Internal variables = Global variables with internal linkage.

`const` and `constexpr` globals are internal variables by default.
To make non-constant global variables internal, the `static` keyword must be used before the defining its type.

`static` can be applied to functions, making them inaccessible outside the file they've been defined in.

## Global variables with external linkage

External linkage = can be seen and used from both the file where it has been defined and other code files.

Functions have external linkage by default.
Forward declaraton is used to inform the compiler about the its existence and the linker then connects the function call to its actual definition.

To make global variables external, apply the `extern` key word when initialising.
However, note that external global variables must still be forward declared (still using `extern`) in other files if they are to be used in them.

`constexpr` can be given external linkage using `extern` but can't be forward declared so there's no value in doing so.

## Why non-const global variables should be avoided

The biggest reason is that their values can be changed by _any_ function that is called making it extremely difficult to keep track of them.
This also makes it difficult to determine what has caused changes and where to look in code.

When using global variables, try to make sure they meet these criteria:
- The varaible only ever represents one thing
- Its use is ubiquitous throughout the program

Else just use local variables.

## Global variable usage

Suggestions for usage include:
- Prefix global variables with "g" or "g\_".
- Put them in a namespace to be accessed via functions.
- Don't write global variables into functions but pass them as arguments instead for modularity.
- Prefer defining global constants as `inline constexpr` in a header file over `extern const` in a separate file if compiler is C++17 capable.

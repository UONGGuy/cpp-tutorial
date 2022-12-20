# Type deduction

C++ requires all objects to be provided with an explicit type.

Type deduction allows the compiler to deduce an object's type from its initialiser.
This can be done for variables and functions.

Type deduction is useful for readability, choosing optimal types and can be helpful in identifying non-initialised variables.

However, they can make it more difficult to track variable typings, and can lead to unexpected behaviour if the type of an initialiser changes.

Overall though, it is safe to use unless a specific type needs to be used.

## Type deduction for initialised variables

Using keyword `auto`, the compiler can deduce an object's type at initialisation.

```cpp
auto d { 5.0 }; // 5.0 is a double literal -> type = double
auto i { 1 + 2 }; // evaluates to an int -> type = int
auto j { i }; // i is an int so j will be one too
```

This can also be used when the intialiser is a function call.

Type deduction does not work if the object doesn't have an initialiser or is empty intialised.

Note that in most cases, type deduction will drop the `const` qualifier from deduced types (i.e. you must call `const auto` for a const deduced type).

## Type deduction for string literals

Due to historical reasons, string literals will be type `const char\*` rather than `std::string`.

To have string literals deduced as `std::string` or `std::string_view`, the `s` or `sv` suffixes must be included.

## Type deduction for functions

Using keyword `auto`, it is possible to detect and return values with their types deduced by the compiler.

```cpp
auto add(int x, int y) // returns an int after type deduction
{
    return (x + y);
}
```

Again, it is important to be wary that if the type of an initialiser changes, the type of the deduced variable may also be affected.

When using an `auto` return type with a function returning fixed values, the function must return values of the same type, otherwise an error will occur.
If such a case is desired, it is better to explicitly convert returned values using `static_cast`.

It is also important to note type deduction cannot be used for function parameters - their types must be explicitly defined.

`auto` defined functions must also be fully defined before they can be used (i.e. forward declaration is not sufficient).
This means normal functions returning `auto` are typically only callable from the files in which they are defined.

It is generally better to favour explicit return types over `auto` for normal functions due to difficulty in determining the type returned by the function if error occurs.

### Trailing return type syntax

`auto` can also be used to declare functions using trailing return syntax which defines the return type after the rest of the function prototype.

```cpp
auto add(int x, int y) -> int // trailing return type syntax defining int type
{
    return (x + y);
}
```

This is useful for lining up all function names and also required for more advanced features of C++ such as lambdas.



# Typedefs and type aliases

Essentially introduces a new identifier for a pre-existing type to the compiler.

Primarily used in platform independent coding to hide platform specific details.
Is common for cross-platorm programs to use a type alias to include the type's size in bits for clarity.
Also used to make complex types easier to read as well as improving general readability and code maintenance ability..

```cpp
// create alias for long type
using VectorPairSI = std::vector<std::pair<std::string, int>>
// use type alias to define variable in function parameter
bool hasDuplicates(VectorPAirSI pairlist)
```

## Type aliases

Through the `using` keyword, an alias for an existing data type can be created.

```cpp
// define Distance as an alias for the type double
using Distance = double;

Distance kmToShop { 2 }; // defines a variable of type double
```

There are three common naming conventions for aliases:
- Aliases ending with suffix "\_t" (may clash with globally scoped type names)
- Aliases ending with suffix "\_type"
- Aliases without any suffix (mainly for nested type aliases)

It is typical to name user-defined type aliases with a capital letter and no suffix in modern C++.

Type alias identifiers follow the same scope as variable identifiers: type aliases defined in blocks have block scope, type aliases defined in the global namespace have file scope.
They can also be defined and included in header files as part of the global namespace.

## Typedefs

Short for "type definition", typedefs are an older way of creating type aliases through the `typedef` keyword.

```cpp
// The following aliases are identical
typedef long Miles;
using Miles = long;
```

They are in C++ for backwards compatibility reasons and should generally be avoided over modern methods of alias creation.

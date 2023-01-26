# User-defined types

C++ allows us to create new, custom types for use in our programs.
Such types are called user-defined types.
There are two categories of compound types allowing for this:
- Enumerated types (inc. unscoped and scoped enumerations)
- Class types (inc. structs, classes and unions)

Officially, user-defined types are any class or enumerated types defined by the user, standard library, or the implementation (compiler).
For additional differentiation, the C++20 language defines the term "program-defined type" to mean class and enumerated types not included by the standard library, implementation, or core language (i.e. program-defined type -> defined by the user).

## Defining user-defined types

User-defined types must be defined by a type definition.
User-defined type definitions always end in a semi-colon.
Not doing this results in an error which can be hard to identify as the compiler usually calls out the line _after_ the type definition.

By convention, user-defined types start with a capital letter and do not use suffixes.

User-defied types should be defined as close to the first point of use as possible if only used in one code file.

## Usage across multi-file programs

If a user-defined type is used in a file, the compiler needs to see the full type definition to use it.
Forward declarations are not sufficient as the compiler needs to know how much memory to allocate for objects of that type.

User-defined types are usually defined in header files and `#include`d into the code file as required.
These header files are often named after the user-defined type.

Unlike functions or global variables, type definitions are partially exempt from the one-definition rule (i.e. a type can be defined in multiple code files) due to the necessity for the full definition to be seen.
Note that the type definitions for a given type must be identical across the mutliple code files else undefined behaviour will result.




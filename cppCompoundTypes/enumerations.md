# Enumerations

Also called an enumerated type or enum, enumerations are compound data types where each value is defined as a symbolic constant known as an enumerator.
Each enumerator is assigned an integer value one greater than the previously listed enumerator.
This value can be manually assigned and duplicate values can be assigned (although these should be avoided unless there is a reason to do so).
They are useful for enhancing code documentation and readability for objects that only need to hold one of the values at any time (e.g. cardinal directions, days of the week, card suits).

Being user-defined types, each enumeration needs to be defined before it can be used.

C++ supports both unscoped and scoped enumerations.

## Unscoped enumerations

Unscoped enums are defined by the `enum` keyword and contain enumerators specifying the set of possible values that objects of the type can hold.
Enumerators are separated by commas within the curly braces and the enumeration definition must end with a semi-colon.

They are unscoped because their enumerator names are in the same scope as the enumeration definition itself.
This means the enumerator names can't be used in multiple enumerations within the same scope.

```cpp
// Defined unscoped enumeration called Colour
enumeration Colour
{
    // Symbolic constants define all possible values this enumeration can hold
    red = -1, // assigned -1
    green, // assigned 0
    blue, // assigned 1
}; // enumeration definition must end with a semi-colon

int main()
{
    Colour apple{ red };
    Colour shirt{ green };
    Colour cup{ blue };

    Colour socks{ white }; // error as "white" is not an enumerator of Colour
    Colour hat{ 2 }; // error as "2" is not an enumerator of Colour
```

Conventionally, enumeration types are named starting with a capital letter and enumerators startng with a lower case letter.

Each enumeration is a distinct type and is distinguised from other types by the compiler (unlke typdefs or type aliases which are non-distinct).
One way to prevent enumerator naming collisions is to prefix each enumerator with the name of the enumeration itself.
A better method is to place the enumeration within a namespace or anything providing a separate scope region.

Unscoped enumerations implicity convert their values to integral values.
If we require the names of the enumerators to be printed, we can either teach `operator<<` how to print them as desired or write a switch or if-else statement.
To each `operator<<` how to print values, we would add the following code:

```cpp
std::ostream& operator<<(std::ostream& out, Colour colour)
{
    switch (colour)
    {
        case red: out << "red"; break;
        case green: out << "green"; break;
        case blue: out << "blue"; break;
        default: out << "???"; break;
    }

    return out;
}
```

If necessary, the base type of an enumeration can be specified.

Note that the compiler will not implicity convert an integer to an unscoped enumerator - an error will be produced.
To work around this, `static_cast` can be used to convert an integer to an unscoped enumerator.

## Scoped enumerations (enumeration classes)

These are safer, strongly typed (won't implicitly convert to integers) and strongly scoped (enumerators only plcaedd into scope region of the enumeration) versions of unscoped enumerations.
To make them, we use the `enum class` keyword.
Everything else is the same as for an unscoped enumeration.
Scoped enumerations act like a namespace for their enumerators and are accessed as such.

Although you can compare enumerators from the same enumeration, if comparing to those from other enumerations, it is best to explicitly convert to an integer using `static_cast`.

Scoped enumerations should always be favoured over unscoped enumerations unless there is compelling reason to do otherwise.

Similar to namespaces, we can use `using enum` to access enumerators from the specified enum class without having to prefix each of them which can be useful when writing code to print enumerator names.


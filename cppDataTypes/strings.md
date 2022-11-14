# Strings

Identified by double quotes, are collections of sequential characters.
Are NOT fundamental types in C++.

Has two safer compound string types, `std::string` and `std::string_view` that can be worked with.

## std::string

Lives in the <string> header.

Create objects similar to others:

```cpp
#include <string> // to use std::string

int main()
{
    std::string name {}; // empty string

    return 0;
}
```

Can be output using `std::cout`.

Better to use `std::getline()` to read full line of input into a string.
`std::cin` only returns characters up to first whitespace encountered.

```cpp
#include <string> // to use std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name {}; // empty string
    std::getline(std::cin >> std::ws, name) // read full ine of text into name

    std:: cout << "Nice to meet you, " << name << std::endl;

    return 0;
}
```

`std::ws` tells `std::cout` to ignore leading whitespace before extraction when using `std::getline()`.
If not, will return the `"\n` from previous input also.

Can find out how many characters is a string using the `.length()` member function.
Note that it returns an unsigned integral value so use `static_cast` to convert to desired type if necessary.

In C++20, can use `std::ssize()` to get `std::string` length as a signed integer.

Can give double-quoted string literals type `std::string` by adding suffix `s` after them.

Try to avoid passing `std::string` by value if possible as it is expensive. Prefer `std::string_view` parameters.

## std::string\_view

Requires the <string\_view> header.

Use for when you need a read-only string - especially for function parameters.
Since initialising `std::string` is expensive, use `std::string_view` where possible to avoid making unnecessary copies.

`constexpr` is supported by `std::string_view` (unlike with `std::string`).

Can initialise a `std::string_view` from a `std::string`.

Can convert a `std::string_view` to a `std::string` using `static_cast`.

Can give double-quoted string literals type `std::string_view` by adding suffix `sv` after them.

Avoid returning a `std::string_view` where possible.

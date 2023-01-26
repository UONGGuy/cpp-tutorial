# Class templates

Similar to function templates, class templates are template definition for instantiating class types (e.g. struct, class or union types).

They can also be used in conjunction with function templates to reduced code redundancy.
For example,

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first > p.second ? p.first : p.second)
}

int main()
{
    Pair<int> p1{ 5, 6 };
    std::cout << max<int>(p1) << " is larger\n";

    Pair<double> p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n"; // calls max<double> using template argmument deduction (prefer this)
    
    return 0;
}
```

### Class templates with template type and non-template type members

It is possible for class templates to have a mix of members using a template types and normal types.

```cpp
template <typename T>
struct Foo
{
    T first{};
    int second{};
};
```

`first` will be the template type `T` and `second` will always be `int`.

It is also possible for multiple template types to be used for struct members.

### std::pair

Due to how common it is to work with pairs of data, the C++ standard library contains class template `std::pair` in the `<utility>` header.
This works similarly to the `Pair` struct defined in the examples above and should be favoured in actual use.

### Using class templates in multiple files

Class templates are typically defined in header files as well so they can be included into multiple code files.

## Class template argument deduction (CTAD) and deduction guides

From C++17 onwards, the compiler can deduce class templates from the object's initialiser when instantiating an object from a class template.

CTAD is only performed if no template argument list is present (i.e. no angled brackets).

```cpp
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

int main()
{
    Pair p1{ 1, 2 }: // CTAD, although compile error in C++17

    return 0;
}
```

### Template argument deduction guides

Note that although the procedure for CTAD is implemented above, in C++17 it doesn't know how to deduce template arguments for aggregate class templates.
To deal with this, we can provide a deduction guide for the compiler.

```cpp
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// deduction guide for how to deduce template arguments for class template
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair p1{ 1, 2 }: // CTAD, now compiles in C++17 too

    return 0;
}
```

Note that `std::pair` and other standard library template types come with their own pre-defined deduction guides so we do not need to write them ourselves.

In C++20, the compiler can automatically generate deduction guides for aggregate class types so there is no need for deduction guides when using this compiler.

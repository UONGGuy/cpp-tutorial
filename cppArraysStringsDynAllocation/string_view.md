# std::string\_view

In C++17, a new way of using strings, `std::string_view` (lives in `<string_view>` header), was introduced.
Unlike `std::string` which keeps its own copy of the string, `std::string_view` provides a view of a string defined elsewhere.

It can essentially take the place of `std::string` and C-style strings when declaring objects.
This prevents multiple copies of the string from being created as the same string is being observed.

As a result, `std::string_view` is faster than `std::string` whilst retaining many similar functions.

```cpp
#include <iostream>
#include <string_view>

int main()
{
    std::string_view str{ "Trains are fast!" };
    
    std::cout << str.length() << '\n'; // 16
    std::cout << str.substr(0, str.find(' ')) << '\n'; // Trains
    std::cout << (str == "Trains are fast!") << '\n'; // 1

    // Since C++20
    std::cout << str.starts_with("Boats") << '\n'; // 0
    std::cout << str.ends_with("fast!") << '\n'; // 1

    std::cout << str << '\n'; // Trains are fast!

    return 0;
}
```

Note that since new copies of the string are not created, any changes to the viewed string are reflected in the `std::string_view`.

```cpp
#include <iostream>
#include <string_view>

int main()
{
    char arr[]{ "Gold" };
    std::string_view str{ arr };

    std::cout << str << '\n'; // Gold

    //Change 'd' to 'f' in arr
    arr[3] = 'f';

    std::cout << str << '\n'; // Golf

    return 0;
}
```

When using a `std::string_view`, it is best to avoid modifications to the underlying string for the remainder of the `std::string_view`'s life to prevent confusion and errors.

Best practice is to prefer `std::string_view` over `std::string` and C-style strings when you only need read-only access unless you can't guarantee the string viewed will live for the lifetime of the `std::string_view`, in which case you should prefer `std::string`.

## View modification functions

There are functions the let us change how we view the string without modifying the string itself.

Functions include:
- `remove_prefix`: removes characters from left side of view
- `remove_suffix`: removes characters from right side of view

```cpp
#include <iostream>
#include <string_view>

int main()
{
    std::string_view str{ "Peach" };

    std::cout << str << '\n'; // Peach

    str.remove_prefix(1); // ignore first char

    std::cout << str << '\n'; // each

    str.remove_suffix(2); // ignore last 2 char

    std::cout << str << '\n'; // ea

    return 0;
}
```

Once modified, a `std::string_view` cannot be reverted to its original view unless it is reset by reassigning the source string to it again.

## Non-null-terminated strings

`std::string_view` doesn't use null terminators to mark the end of the string as it keeps track of its length to determine where it ends.

```cpp
#include <iterator> // for std::size
#include <string_view>

int main()
{
    // No null-terminator
    char vowels[]{ 'a', 'e', 'i', 'o', 'u' };

    // vowels not null-terminated so need to pass length manually
    std::string_view str{ vowels, std::size(vowels) };

    return 0;
}
```

## Ownership

A `std::string_view` has lifetime dependent on the string it views.
If the string viewed is destroyed before the `std::string_view`, it will cause undefined behaviour.
This includes modifying a `std::string` as the `std::string_view` will look to where the old string used to exist (but does so no longer).

Remember that `std::string_view` can only view created objects - it can't create any strings on its own.

## Converting a `std::string_view` to a C-style string

This may be useful where old functions require C-style strings.
To convert from `std:: string_view` to a C-style string, we need to first convert to a `std::string`.

```cpp
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view sv{ "balloon" };

    sv.remove_suffix(3);

    std::string str{ sv }; // std::string from std::string_view

    auto szNullTerminated{ str.c_str() }; // get null-terminated C-style string

    std::cout << str << " has " << std::strlen(szNullTerminated) << " letter(s)\n";

    return 0;
}
```

Note it can get expensive creating a `std::string` every time we want to pass a `std::string_view` as a C-style string.

We can also access the string viewed by using the `data()` function to return a C-style string.
This provides fast access to the viewed string as a C-string but should only be used when the viewed string is null-terminated else we risk undefined behaviour.

## Passing strings

We can pass strings either by `const std::string&` or `std::string_view`.

If we want to write a function taking a string parameter, `std::string_view` is most flexible as it works efficiently with C-style strings and `std::string` arguments are implicitly converted to `std::string_view`.

Typically, `std::string_view` is fast to copy so it is usually passed by value rather than const reference as this is optimal for cheap-to-copy types.

The one case where it is generally better to pass a `const std::string&` is when your function needs to call another function that takes a C-style string or `std::string` parameter as `std::string_view` is not guaranteed to be null-terminated.

## Incomplete implementation

`std::string_view` is a relatively recent feature so isn't implemented as well as it could be.
Features that don't work as expected will most likely be supported in future versions of C++.

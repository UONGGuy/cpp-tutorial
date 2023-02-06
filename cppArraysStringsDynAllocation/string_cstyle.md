# C-style strings

Earlier, strings were defined as collections of sequential characters and `std::string` (from the standard library) was used as the method of working with them.

Modern C++ also supports C-style strings as inhereted from the C language.
Although these are important to be aware of due to their prevalence in a lot of code, it is preferred to use `std::string` or `std::string_view` as they are easier, safer, and more flexible.

A C-style string is an array of characters that uses a null terminator.
A null terminator is a special character ('\0', ascii code 0) used to indicate the end of a string.
This leads to C-style strings also being called null-terminated strings.

## Defining C-style strings

C-style strings are declared as char arrays initialised with a string literal:

```cpp
char myString[]{ "string" };
```

C++ automatically adds a null terminator to the end of the string (this makes it an array of length 7 rather than 6).

It is important to note C-style strings follow all the same rules as arrays.
This means the string can be initialised upon creation but values can't be assinged to it using the assignment operator after.

```cpp
char myString[]{ "string" }; // accepted
myString = "rope"; // does not change myString
```

Individual characters can be changed by assinging new char to the indices of letters we want to adjust.

```
char myString[]{ "string" }; 
myString[1] = 'p'; // myString -> "spring"
```

When C-style strings are printed, `std::cout` prints characters until it encounters the null terminator.
If you accidentally overwrite the null terminator (e.g. by assigning a value over it), `std::cout` continues to print everything in adjacent memory slots until it hits a zero.

Note it is fine for the array length to be greater than the string it contains. 
In this case, everything past the null terminator will not be printed.

## Reading in C-style strings

When reading in strings, we can declare an array much larger than we need in order to avoid losing information from the input.
The recommended way of reading C-style strings using `std::cin` is as ollows:

```
#include <iostream>
#include <iterator> // for std::size

int main()
{
    char name[255]{}; // declare array large enough for 254 char + null terminator
    std::cout << "Enter your name: ";
    std::cin.getline(name, std::size(name)); // don't need .getline() but prevents array overflow by discarding excess characters.
    std::cout << "Hello, " << name < '\n';

    return 0;
}
```

## Manipulating C-style strings

There are many functions available in the `<cstring>` header that allow C-style strings to be manipulated.
A few useful ones are as follows:
- `strcopy(dest, source)`: allows one string to be copied to another but can cause array overflows if `dest` not big enough.
- `strcpy_s(dest, dest_size, source)`: similar to `strcopy()` but with param for destination size. Not supported by all compilers and need C++11, have to define `STDC_WANT_LIB_EXT1` with integer value 1 to use: `#define __STDC_WANT_LIB_EXT1__ 1`
- `strlen(string)`: returns number of char in C-style string excluding null terminator
- `strncat()`: appends one string to another with buffer length check
- `strcmp()`: compare two strings (returns 0 if equal)
- `strncmp()`: compare two strings up to a specific number of characters (returns 0 if equal)

## C-style string symbolic constants

It is possible to create C-style string symbolic constants using pointers.

```cpp
int main()
{
    const char* myName{ "Alex" }; // pointer to string literal

    return 0;
}
```

This differs from the fixed array initialisation of C-style strings.

In the fixed array case, memory is allocated and initialised with the string + null terminator.
Memory allocation allows the array contents to be altered with the array being treated as a normal local variable (i.e. when it goes out of scope, its memory is freed up for other uses).

In this string literal case, what usually happens is that the string literal + null terminator is placed into read-only memory and a pointer is set to it.
String literals can't be changed so the string must be const.
It is possible that the compiler may consolidate multiple string literals into a single value to optimise memory (e.g. 2 pointers to two identical string literals -> 2 pointers to the same string literal).
String literals have static duration rather than automatic due to being stored in a fixed location in memory and so scoping issues are not a concern.
This means they can be used to avoid dangling pointers when returning pointers from functions.

## std::cout and char pointers

The type of a pointer affects how it interacts with `std::cout`.
For non-char pointers, `std::cout` will print the contents of the pointer (i.e. the memory address it holds).
For `char*` or `const char*` type objects, it assumes you want to print a string and so prints the string being pointed to instead.

This can occasionally lead to unexpected results but is unlikely to occur much in practice as you're unlikely to want to print memory addresses.


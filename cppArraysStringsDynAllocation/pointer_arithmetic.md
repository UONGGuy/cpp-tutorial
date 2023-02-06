# Pointer arithmetic

C++ allows integer addition/subtraction operations on pointers.
For a pointer `ptr` pointing to an integer,
- `ptr + 1` is the address of the next integer in memory after `ptr`
- `ptr - 1` is the address of the previous integer in memory before `ptr`

Note that what is returned is not the memory address after `ptr`, but the memory address of the next object of that type that `ptr` points to.

If `ptr` points to an integer (assume size 4 bytes), `ptr + 3` means 3 integers (12 bytes) after `ptr`.
If `ptr` points to a character (always 1 byte), `ptr + 3` means 3 characters (3 bytes) after `ptr`.

The compiler always multiplies the integer operand by the size of the object bing pointed to (scaling).

## Relation to arrays and indexing

We can see arrays are laid out sequentially in memory if we print their memory addresses using the address-of operator (&).

Remembering that a fixed array decays into a pointer that points at the first element of the array, we can cause it to point at other elements by applying pointer arithmetic logic.


```cpp
#include <iostream>

int main()
{
    int array[]{ 9, 7, 5, 3, 1 };

    std::cout << &array[1] << '\n'; // memory address of array[1]
    std::cout << array + 1 << '\n'; // memory address of array pointer + 1

    std::cout << array[1] << '\n'; // 7
    std::cout << *(array + 1) << '\n'; // 7 (note: parenthesis needed)

    return 0;
}
```

Essentially, `array[n]` is equivalent to `*(array + n)`, which is how the compiler interprets the subscription operator ([]).

The following expressions are equivalent to the compiler:
```cpp
arr[2] // use
*(arr + 2) // use
*(2 + arr) // can use
2[arr] // avoid
```

### Iterating through an array using a pointer

We can loop through an array using a pointer and pointer arithmetic.
It's less common as subscripts are generally easier to read and less error prone, but an example is as follows:

```cpp
#include <iostream>
#include <iterator> // std::size

bool isVowel(char c)
{
    switch (c)
    {
        case 'A':
        case 'a':
        case 'E':
        case 'e':
        case 'I':
        case 'i':
        case 'O':
        case 'o':
        case 'U':
        case 'u':
            return true;
        default:
            return false;
    }
}

int main()
{
    char name[]{ "Mollie" };
    int arrayLength{ static_cast<int>(std::size(name)) };
    int numVowels{ 0 };

    for (char* ptr{ name }; ptr != (name + arrayLength); ++ptr)
    {
        if (isVowel(*ptr))
        {
            ++numVowels;
        }
    }

    std::cout << name << " has " << numVowels << " vowels.\n';

    return 0;
}
```

Since counting elements is common, the algorithm library offers `std::count_if` as a means of counting elements that fulfil a given condition.
This can replace the for loop in the above example:

```cpp
auto numVowels{ std::count_if(std::begin(name), std::end(name), isVowel) } ;
// could also replace std::begin and std::end with name and (name + nameLength)
```




# Object-Oriented Programming: Static member

The `static` keyword turns variables global so they are not destroyed when they go out of scope.
When applied to member variables and member functions, the usage changes slightly.

## Static member variables

Applying `static` to a class member variable turns it into a value that is shared between all objects of the class.

Although static members are accessible through objects of the class, they are not explicitly associated with specific objects.
They exist even if no objects of said class have been instantited, being created when the program starts and destroyed when it ends.

Because static member variables exist independently of any class objects, they can be accessed directly using the class name and scope resolution operator (e.g. `Something::static_member_var`).

We can still access and use a static member variable - even if no objects of that type have been instantiated yet.

### Defining static member variables

When a static member variable is declared in a class, we inform the compiler it exists but don't actually define it (c.f. forward declaration).
Defining the static member variable happens outside the class and in th global scope.
If not initialiser is provided, C++ zero-initialises the value.

Note that static member definitions are not subject to access controls meaning they can be defined and initialised even if declared as private or protected in the class.
(However, if they are not public, they may not be accessible)

If the class is defined in a .h file, the static member definition is usually placed in the associated code file.
It is best to avoid placing the static member definition in a header file as if the header file is included more than once, there will be multiple definitions and a linker error will occur.

### Inline initialisation of static member variables

When a static member is a const integral type (inc. char and bool), a const enum, or static constexpr it can be intialised inside the class defintion.
As of C++17, non-const static member can be declared inline in the class definition too.

```cpp
#include <array>

class Something
{
public:
    static const int s_value{ 4 }; // static const int can be declared and initialised directly
    static constexpr std::array<int, 3> s_array{ 1, 2, 3 }; // works for classes supporting constexpr intitialisation
    static inline int s_value2{ 4 }; // static inline int can be declared and initialised directly (C++17)
};
```

Best practice is to prefer initialising static constexpr members at the point of definition.
For static non-constexpr members, make them `inline` and initialise at the point of defintion.

## Static member functions

Static member functions are also not attached to any particular object similar to static member variables.
They can also be called by prefixing with the class name and scope resolution operator.
Although they can be called through objects of the class type, this is not recommended.

```
class Something
{
private:
    static int s_value;

public:
    static int getValue() { return s_value; } // static member function
};

int Something::s_value{ 1 }; // initialiser

int main()
{
    int x{ Something::getValue() };

    return 0;
}
```

Two properties of static member functions are that they have no `this` pointer (as they are not attachd to an object) and they can directly access other static members (variables and functions) but not non-static members (as non-static members belong to a class object but static member functions are not associated with specific objects).

### Defining static member functions

Static member variables can also be defined outside the class declaration in the same way as normal member functions.

## Other noteworthy topics

### Monostates

Monostates are class with all static members.
While they can be useful, it is important to remember it's not possible to have multiple coopies of it without cloning and renaming the class due to its static property.

They also share the same downsides as global variables as a pure static class is equivalent to declaring functions and global variables in a globally accessible namespace.

### Static constructors are not supported

Static members cannot be initialised via static constructor in C++ - they must be directly initialised.
If initialising the static member variables requires executing code, a lambda can be used to call it immediately.

```cpp
#include <vector>

class MyClass
{
public:
    static std::vector<char> s_mychars;
};

std::vector<char> MyClass::s_mychars{
    [] {// Parameter list of lambdas without parameters can be ommitted
        // Can declare another vector and use a loop here
            std::vector<char> v{};

            for (char ch{ 'a' }; ch <= 'z'; ++ch)
            {
                v.push_back(ch);
            }

            return v;
        } () // Call lambda right away
};
```

An example more like a regular constructor:

```cpp
#include <vector>

class MyClass
{
public:
    static std::vector<char s_mychars;

    class init_static // define nested class init_static
    {
    public:
        init_static() // constructor to initialise static variable
        {
            for (char ch{ 'a' }; ch <= 'z', ++ch)
            {
                s_mychars.push_back(ch);
            }
        }
    };

private:
    static init_static s_initialiser; // use this static object to ensure init_static constructor is called
};

std::vector<char> MyClass::s_mychars{}; // define static member variable

MyClass::init_static MyClass::s_initialiser{}; // define static initialiser, which will call init_static constructor, which will initialise s_mychars
```

When `s_initialiser` is defined, the `init_static()` default constructor will be called.
This can be used to initialise any static member variables.
This solution continues to keep initialisation code hidden within the original class.




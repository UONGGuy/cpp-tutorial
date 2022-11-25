# Namespaces

Naming collisions occur when identical identifiers are introduced into the same scope and the program cannot distinguish which to use.

For simple programs, identifiers can be changed for clarity but for larger programs, it may be better for the user to define their own namespaces.

This can be done like such:
```cpp
namespace foo
{
    // Code block with objects belonging to this namespace
}
```

Objects within the namespace can be called in the following way:
```cpp
foo::function
```

If the scope resolution operator is used without a namespace provided, (e.g. `::function`), then the identifier is looked for in the global namespace.

It is legal to declare namespace blocks in multiple locations - either across multiple files or multiple places in the same file.
However, if the namespace is ommitted in the source file, the linker will not be able to find the desired definition for it.

Namespaces can also be nested inside other namespaces:
```cpp
#include <iostream>

namespace foo
{
    namespace goo
    {
        void bar()
        {
            std::cout << "bar\n";
        }
    }
}

int main()
{
    foo::goo::bar();
    return 0;
}
```

Namespace aliases can be used to shorten a long sequence of namespaces for ease of use and updating.
For example:

```cpp
#include <iostream>

namespace foo::goo
{
    void bar()
    {
        std::cout << "bar\n";
    }
}       

int main()
{
    namespace active = foo::goo; // active refers to foo::goo
    
    active:bar();

    return 0;
} // the alias 'active' ends here
```

## Unnamed (anonymous) namespaces

Refers to namespaces defined without a name.

```cpp
namespace // unnamed namespace
{
    // content
}
```

All content declared in an unnamed namespace is treated as if it is part of the parent namespace.

The key reason they are used is because all identifiers within an unnamed namespace are treated as if they have internal linkage (i.e. contents can't be seen outside of the file where content is defined).
For functions defined in an unnamed namespace, they essentially all become static functions.

## Inline namespaces

Inline namespaces are defined using the `inline` keyword and typically used to version (update) content.

Content within inline namespaces are considered part of the parent namespace but not everything is given internal linkage.

```cpp
#include <iostream>

inline namespace v1 // declare inline namespace v1
{
    void doSomething()
    {
        std::cout << "v1\n";
    }
}

namespace v2 // normal (updated) namespace v2
{
    void doSomething()
    {
        std::cout << "v2\n";
    }
}

int main()
{
    v1::doSomething(); // calls version 1
    v2::doSomething(); // calls version 2

    doSomething(); // calls inline version (v1 in this case)
}
```

By changing which namespace is inline, it is easier to globally update programs.



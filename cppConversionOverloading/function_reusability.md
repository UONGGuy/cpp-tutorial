# Function reusability

One of the key mandates for good coding practice is to follow the "DRY rule" (Do Not Repeat Yourself).
In the case you end up with multiple functions that perform similar functions (see also Function Overloading) or have a certain argument value that is predominantly used, C++ has methods of covering both.

## Default arguments

A default argument is a way of pre-defining a value for a function parameter in the case the caller doesn't provide one themself.

```cpp
void print(int x, int y = 10) // 10 is the default argument for y
{
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
}
```

If an argument is explicitly specified, then the default argument will not be used and the function will use the specified argument.

Note that default arguments can only be provided for the rightmost parameters else it's not possible to call the function's default arguments implicitly.

It's best to order arguments left-to-right by most to least likely to require user input.

If using forward declaration, best practice is to put the default argument there rather than in the function definition.

Functions with default arguments may be overloaded but can lead to ambiguous function calls.

## Function templates

The template system in C++ simplifies creating functions or classes that are able to work with different data types.
Programming with templates is sometimes called generic programming.

A template describes what the function or class looks like but using placeholder/template types that are provided later.
Once defined, the compiler can generate as many overloaded functions or classes as it needs from the template using defined actual types.

It is much easier to create and maintain than a list of overloaded functions.

Due to actual types not being determined until template usage, the author doesn't have to try and anticipate all of the actual types that might be used.
This leads to template types sometimes being called generic types.

An  example implementation of a template that returns the larger of two values is:

```cpp
template <typename T> // template parameter declaration
T max(T x, T y) //function template definition for max<T>
{
    return (x > y) ? x : y;
}
```

Template types are usually denoted by a single capital letter.
It is possible to definte multiple template types if necessary.

### Template instantiation

Following from the example, to use the function template, we make a function call with the following syntax:

```cpp
max<actual_type>(arg1, arg2); // replace actual_type with desired data type
```

An example program might look like this:

```cpp
#include <iostream>

template <typename T> // template parameter declaration
T max(T x, T y) //function template definition for max<T>
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; //instantiates and calls function max<int>(int, int)
    
    return 0;
}
```

When the compiler encounters this function call, it will use the `max<T>` function template to create a function given it doesn't already exist.

The compiler essentially clones the function template and replaces the template type (`T`) with the specified type.
 
### Template argument deduction

It is possible for the compiler to deduce the template type from its arguments if it is not explicitly defined in the angled brackets or the angle brackets are not included.
Although same in essence, calling `max<>(1, 2)` versus `max(1, 2)` will lead to a difference in how the compiler resolves function calls.
The former will only consider `max<int>` template function overloadswhereas the latter considers both `max<int>` template function overloads AND `max` non-template function overloads.

Generally preferred syntax for calling function templates is not to include the angled brackets.

Errors can still occur if the deduced type does not make any sense with the actions the template outlines.

### Function templates with non-template parameters

It is possible to create functions with both template type and non-template type parameters.
The template parameters are matched to any type and the non-template parameters work like the parameters of normal functions.

### Template usage across multiple files

The compiler needs to see the full definition of the template for it to be instantiated.
As such, they are typically written into header files where they can be `#include`d into any code files that may require their use.

### Function templates with multiple template types

Although template types are powerful in that they allow for the deduction of argument type, each template type can only represent one actual type.

In the example above, if we have one `int` argument and the other as `double`, the compiler will not be able to create a template for `max(int, double)` as both parameters are expected to be of the same type `T`.

To circumvent this, we can either explicitly cast arguments to match types, write a non-template function, specify the type `T` in the angled brackets, or define an additional template type parameter.

Defining an additional template type parameter means the compiler can now instantiate `max<int, double>(int, double)`.

Note however, that we are now subject to errors through mismatched typings (e.g. arithmetic rules for operators).
One method that may sometimes resolve this issue is defining the return type of the template as `auto` to allow the compiler to deduce the return type from the return statement.

```cpp
#include <iostream>

template <typename T, typename U> //define 2 template type parameters
auto max(T x, U y) //x resolves to type T, y resolves to type U
{
    return (x > y) ? x : y; 
}

int main()
{
    std::cout << max(1, 2.5) << '\n'; // may end up with narrowing conversion problem 
    
    return 0;
}
```

In C++20, the `auto` keyword can also be used as a parameter type and in an equivalent manner as an independent template type parameter.
Templates created in this manner are called abbreviated function templates.

```cpp
auto max(auto x, auto y) 
{
    return (x > y) ? x : y; 
}
```

### Drawbacks to template usage

The compiler creates and compiles a function for each function call with a unique set of argument types so may expand out and lead to bloated code and slow compile times.
Function templates can also produce error messages that can be much harder to decipher (but equally as useful).

Despite this, templates have very versatile usage and can be used liberally where type flexibility is needed.

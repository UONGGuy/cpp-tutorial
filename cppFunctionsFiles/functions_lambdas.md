# Lambdas (anonymous functions)

Lambda expressions (also called lambdas or closures) allow anonymous functions to be defined inside another function.
Nesting is important as it avoids polluting the namespace and allows this function to be defined close to its usage, providing context.
They are called anonymous functions as they tend to be trivial functions that are not named.

The syntax for lambdas is:
```cpp
[ captureClause ] ( parameters ) -> returnType
{
    statements;
}
```

- The capture clause can be empty if no captures are required
- The parameter list can be empty or ommitted if no parameters are requried
- The return type is optional and assumed `auto` if ommitted.

A trivial lambda definitions looks like this:
```cpp
int main()
{
    [] {}; // lambda with no captures, ommitted params, ommitted return type

    return 0;
}
```

An example usage could be for a search function condition:
```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main()
{
    constexpr std::array<std::string_view, 4> arr{ "apple", "bannana", "walnut", "lemon" };

    // Define function where used
    const auto found{std::find_if(arr.begin(), arr.end(), 
        [](str::string_view str) // lambda, no capture clause
        {
            return (str.find("nut") != std::string_view::npos);
        }) 
    };

    if (found == arr.end())
    {
        std::count << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    return 0;
}
```
Best practice is to define things in the smallest scope and closest to first use meaning lambdas are preferred over normal functions when trivial, one-off functions are needed to pass arguments to another function.

## Types of lambda

In the above example, we defined a lambda where it was needed.
This usage is called a function literal.

We can also initialise a lambda variable with a lambda definition then use it later.
This can make code easier to read.
```cpp
// Store lambda in a named variable and pass it to a function
auto isEven{
    [](int i)
    {
        return ((i % 2) == 0);
    }
};

// Call lambda from named variable
return std::all_of(array.begin(), array.end(), isEven);
```

Although we give the lambda type `auto`, lambdas don't have a type we can explicity use - compilers generate a unique type for them.

Despite this, we can store lambdas for post-definition use in many ways.
If the lambda has an empty capture clause, we can use a regular function pointer.
We can also use `std::function` or the `auto` keyword.
```cpp
#include <functional>

int main()
{
    // Regular function pointer.
    // Only works with empty capture clause
    double (*addNumbers1)(double, double){
        [](double a, double b){
            return (a + b);
        }
    };
]
    // Using std::function.
    std::function addNumbers2{
        [](double a, double b){
            return (a + b);
        }
    };
        
    // Using auto
    auto addNumbers3{
        [](double a, double b){
            return (a + b);
        }
    };

    return 0;
}
```

Prior to C++20, `auto` can't always be used where the actual lambda is not known since functions must know what parameter type is being called in.
To fix this, `std::function` can be used instead.
```cpp
#include <functional>
#include <iostream>

// Don't know what fn will be.
// Use std::function with regular functions and lambdas
void repeat(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{ 0 }; i < repetitions, ++i)
    {
        fn(i);
    }
}

int main()
{
    repeat(3, [](int i) {
        std::cout << i << '\n';
    });

    return 0;
}
```

Because they are actually templates, functions with `auto` parameters cannot be separated into a header and source file.

## Generic lambdas

When a lambda has one or more `auto` parameter, the compiler will infer what types are needed from the calls to the lambda.
These type of lambdas are called generic lambdas due to their wide variety of use cases.

Be wary that `auto` isn't the best choice of parameter type as some objects (e,g. C-style strings) aren't easy to work with and `auto` may infer a type we don't expect it to.

Note also that a unique lambda will be generated per different type that `auto` resolves to.
This can cause problems if we use them with static duration variables as the variables are not shared between generated lambdas.

## Return type deduction and trailing return types

If return type deduction is used, a lambda's return type is deduced from the `return` statements it contains (if multiple, they must all return the same type).
To avoid hassle, a return type for the lamda can be explicitly specified to let the compiler do implicit conversions.
This means you only usually need to change the lambda's return type and can avoid touching the lambda body if you need to adjust it.

## Standard library function objects

There exist many common operations in the standard library (many in the `<functional>` and `<algorithm>` headers) that mean we do not need to write as many lambdas as we may think.

## Capture clauses

Lambdas can only access specific identifiers: global identifiers, entities known at compile time, and entities with static duration.
To get around this, lambdas have capture clauses.
These are used to indirectly give a lambda access to variables available in the surrounding scope it would not usually have access to.
```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
    std::array<std::string_view, 4> arr{ "apple", "bannana", "walnut", "lemon" }; // not accessible at compile time

    std::cout << "Search for: ";

    std::string search{};
    std::cin >> search;

    // Capture search
    auto found{ std::find_if(arr.begin(), arr.end(),
        [search](std::string_view str) {
            return (str.find(search) != std::string_view::npos);
        })
    };

    if (found == arr.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    return 0;
}
```

When a lambda definition is exeuted, for each variable it captures, a clone of that variable is made inside the lambda.
While cloned variables share the same name, they may not have the same type as the original variable.

## Captured variables

By default, variables are captured by const value.
This means the lambda cannot modify them and a compile error occurs if we try to do so.

To modify captured variables, we mark the lambda as `mutable` which removes the `const` qualifier from all variables captured by value.
```cpp
#include <iostream>

int main()
{
    int ammo{ 10 };
    
    auto shoot{
        // Add mutable after parameter list
        [ammo]() mutable {
            --ammol
    
            std::cout << "Pew! " << ammo << " shot(s) left.\n";
        }
    };

    shoot(); // 9 shots
    shoot(); // 8 shots

    std::cout << ammo << "shot(s) left\n; // 10 shots

    return 0;
}
```

Note that because the captured variable is a copy of the original, that te value of `ammo` is preserved across calls to the lambda.

## Capture by reference

We can also capture variables by reference to allow our lambda to affect the value of the argument.
All we need to do is prepend an ampersand to the captured variable name (e.g. `&ammo`).

Variables captured by reference are non-const unless the variables themselves are const.
This means we do not need to use the `mutable` keyword.

Capture by reference should be favoured over capture by value in the same way you would prefer passing an argument to a function by reference (e.g. for non-fundamental types).

Mutliple variables can be captured by separating them with a comma.
This can include a mix of those captured by value or reference.

## Default captures

This is a method of capturing all variables mentioned in the lambda body without having to list them explicitly in the capture clause.
This can be initiated by putting symbols into the capture clause:
- `[=]` captures all used variables by value
- `[&]` captures all used variables by reference

These can be mixed with normal captures if we want to specify which variables we want to specifically capture by value or reference.
The caveat is that each variable can only be captured once and the default capture must be the first element in the capture clause.
```cpp
int health { 33 };
int armour { 100 };
std::vector<Enem> enemies{};

[health, armour, &enemies](){}; // legal

[=, &enemies](){}; // legal
// enemies by reference, all others by value

[&, armour](){}; // legal
// armour by value, all others by reference

[&, &armour](){}; // illegal
// already specified all to be captured by reference

[=, armour](){}; // illegal
// already specified all to be captured by reference

[armour, &health, &armour](){}; // illegal
// armour appears twice

[armour, &](){}; // illegal
// default capture must be first element in capture clause
```

## Defining new variables within the lambda capture

We can capture a variable with a slight modification or declare a new variable only visible in the scope of the lambda by defining a variable in the capture clause without specifying its type.
```cpp
#include <algorithm>

int main()
{
    std::array areas{ 100, 25, 121, 40, 56 };

    int width{};
    int height{};

    std::cout << "Enter width and height: ";
    std::cin >> width >> height;

    // Areas are stored
    // User enters width and height
    // Need to calculate area before can search

    auto found{ std::find_if(areas.begin(), areas.end(),
        [userArea{ width * height}](int knownArea) {
            return (userArea == knownArea);
        })
    };

    if (found == areas.end())
    {
        std::cout << "Area not found\n";
    }
    else
    {
        std::out << "Area found\n"
    }
    
    return 0;
}
```

`userArea` will only be calculated once, when the lambda is defined.
If it is to be calculated every time, then the lambda must be mutable (original value will be overwritten).

Best practice is to define the variable outside the lambda then capture it.

## Dangling captured variables

Variables are captured where the lambda is defined.
If a variable that is captured by referece dies before the lambda, the lambda will be left holding a dangling reference.

```cpp
#include <iostream>
#include <string>

// Function to return a lambda
auto makeWalrus(const std::string& name)
{
    // Capture name by reference and return lambda
    return [&]() {
        std::cout << "I am a walrus, my name is " << name << '\n';
    };
}

int main()
{
    // variable holding the lambda returned by makeWalrus
    auto sayName{ makeWalrus("Roofus") };
    // call to makeWalrus creates temporary std::string from string literal
    // temp string dies when makeWalrus returns but lambda still references it

    sayName(); // call lambda returned by makeWalrus
    // undefined behaviour

    return 0;
}
```

Be careful when capturing variables by reference - especiall with default reference capture.
The captured variables must outlive the lambda.

If we want the captured `name` to be valid when the lambda is used, we need to capture it by value rather than by reference.

### Unintended copies of mutable lambdas

Lambdas are objects so can be copied.
This means we should be wary about whether the lambda intended is being called or if a copy is being executed on as standard library functions may copy function objects.

If we need to pass a mutable lambda without the possibility of unintended copies, we can use a non-capturing lambda and use a static local variable instead or prevent copies from being made.

The latter is a better solution with `std::reference_wrapper` from the `<functional>` header allowing us to pass a normal type as if it were a reference.
This can be created using the `std::ref()` function and when a lambda is wrapped in a `std::reference_wrapper`, a copy of the reference to the lambda will be made instead of a copy of the lambda itself.

That is, `std::function` doesn't create a copy of the lambda if it is created with `std::ref()`.

In general, mutable lambdas should be avoided where possible as they are harder to understand and can lead to more issues when parallel execution is required.

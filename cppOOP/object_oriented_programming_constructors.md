# Object-Oriented Programming: Member initialisation

There are some proceedures that the user should be aware of if they want to initialise member variables.

In particular, private members should be initialised using constructors and non-static member initialisation.

## Constructors

When all members of a class (or struct) are public, we can use aggregate initialisation to initialise the class (or struct) directly with list-initialisation.
However, if there are private member variables, then this style of inidialisation does not work.

Constructors are a type of class member function that are automatically called when an object of that class is created.
They are used to initialise member variables to user-provided values or do any set-up steps required for the class to be used (e.g. open a file or database).

Constructors have specific naming rules that must be followed:
- They must have the same name as the class with the same capitalisation
- They have no return type (even void)

### Default constructors

Default constructors are those which take no parameters/has parameters that all have default values.
They are called if no user-provided values are given.

```cpp
class Fraction
{
private: 
    int m_numerator{};
    int m_denominator{};

public:
    Fraction() // default constructor
    {
        m_numerator = 0;
        m_denominator = 1;
    }

    int getNumerator() { return m_numerator; }
    int getDenominator() { return m_denominator; }
    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
};

int main()
{
    Fraction frac1; // default-initialisation -> calls Fraction() default constructor
    Fraction frac2{}; // value-initialisation with empty set -> calls default constructor

    return 0;
}
```

### Value-initialisation

As seen above, value-initialising a class object with an empty set calls the default constructor.

The main reason to favour value-initialisation over default-initialisation is that there is a chance the class may not have a default-constructor and using default-initialisation syntax here will lead to undefined behaviour as nothing is actually initialised.

As such, value-initialisation should be valued over default-initialisation for class objects.

### Direct- and list-initialisation

Constructors can also be declared with parameters for initialisation.

```cpp
#include <cassert>

class Fraction
{
private: 
    int m_numerator{};
    int m_denominator{};

public:
    Fraction() // default constructor
    {
        m_numerator = 0;
        m_denominator = 1;
    }

    Fraction(int numerator, int denominator=1)
    {
        assert(denominator != 0 && "Denominator is zero.");
        m_numerator = numerator;
        m_denominator = denominator;
    }

    int getNumerator() { return m_numerator; }
    int getDenominator() { return m_denominator; }
    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
};

int main()
{
    Fraction fiveThirds{ 5, 3 }; // list-initialisation -> calls Fraction(int, int)
    Fraction threeQuarters(3, 4); // direct-initialisation with empty set -> calls Fraction(int int)
    Fraction six{ 6 }; // calls Fraction(int, int=1)

    return 0;
}
```

Favour brace/list initialisation when initialising class objects.

### Copy initialisation

Copy initialisation is also valid for class objects but it is suggested this is avoided since it may be  less efficient.

### Reducing constructors

The previous example can be rewritten to reduce the number of constructor functions:

```cpp

    Fraction(int numerator=0, int denominator=1)
    {
        assert(denominator != 0 && "Denominator is zero.");
        m_numerator = numerator;
        m_denominator = denominator;
    }
```

This way we have a default constructor that can accept none, one or two user-provide values.

### Implicitly generated default constructor

If you do not define a default constructor for your class, C++ will automatically generate a public one for you.

```cpp
class Date
{
private:
    int m_year{ 1900 };
    int m_month{ 1 };
    int m_day{ 1 };
};

int main()
{
    Date date{}; // Compiler generates default constructor to create object without arguments

    return 0;
}
```

### Default keyword

If you have defined a constructor in your class but want to allow default construction, you can either add default arguments to every parameter of the defined constructor or explicitly define a default constructor.
The `default` keyword allows a default constructor that does nothing to be created.

```cpp
class Date
{
private:
    int m_year{ 1900 };
    int m_month{ 1 };
    int m_day{ 1 };

public:
    Date() = default; // default constructor created
    
    Date(int year, int month, int day) // normal non-default constructor
    {
        m_year = year;
        m_month = month;
        m_day = day;
    }
};

int main()
{
    Date date{}; // initialise to 01 Jan 1990
    Date today{ 2023, 03, 04 } // initialise to 04 Mar 2023

    return 0;
}
```

### Classes containing class type members

Classes can contain other class objects as member variables.
When the outer class is constructed, member variables will have their default constructors called by default.
This happens before the body of the constructor exectutes.

```cpp
#include <iostream>

class A
{
public:
    A() { std::cout < "A\n"; }
};

class B
{
private: 
    A m_a; // B contains A as a member variable

public:
    B() { std::cout << "B\n"; }
};

int main()
{
    B b; // prints A\n B\n

    return 0;
}
```

In constructing variable `b`:
1. The `B()` constructor is called.
2. `m_a` is initialised by calling the `class A` default constructor before the body of the constructor for `B()` is called.
3. Control returns back to the `B()` constructor and executes the body.

### Member initialiser lists

Certain types of data (e.g. const and reference variables) must be initialised on the same line they are declared.
This means that it is not possible to assign values to const or reference member values in the body of the constructor.

To work around this, C++ allows class member variables can be initialised via a member initialiser list (not to be confused with list initialisation).

```cpp
class Something
{
private:
    int m_value1{};
    double m_value2{};
    char m_value3{};

public:
    Something(): m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' } // initialise member variables
    {
        // no need for value assignment here
    }
};
```

The member initialiser list is inserted after the constructor parameters, beginning with a colon and listing a value to initialise each value to separated by commas.
The list is not ended in a semicolon.

It is possible to have user-provided values initialiser class members using this method:

```cpp
class Something
{
private:
    int m_value1{};
    double m_value2{};
    char m_value3{};

public:
    Something(int value1, double value2, char value3='c'): m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 } // directly initialise member variables
    {
        // no need for value assignment here
    }
};

int main()
{
    Something something{ 1, 2.2 };
    Something somethingElse{ 2, 4.5, b };

    return 0;
}
```

The member initialiser list is inserted after the constructor parameters, beginning with a colon and listing a value to initialise each value to separated by commas.
The list is not ended in a semicolon.

It is possible to have user-provided values initialiser class members using this method:

It is best practice to use member initialiser lists to initialise class member variables instead of assignment.

### Initialising const member variables

Classes can contain const member variables which can be initialised using a constructor member initialisation list and the initialisation value can be const or non-const.

```cpp
class Something
{
private:
    const int m_value;

public:
    Something(int x) : m_value{ x } // directly initialise const member variable
    {
    }
};

int main()
{
    int x{ 5 };
    Something s{ x };

    return 0;
}
```

### Initialising array class members

Classes can contain arrays as members.

```cpp
class Something
{
private:
    const int m_array[5];
};
```

Prior to C++11, array members could only be zero initialied via a member initialisation list.

```cpp
class Something
{
private:
    const int m_array[5];

public:
    Something() : m_array{} // zero initialise member array
    {
    }
};
```

Since C++11, member arrays can be fully initialised using uniform initialisation.

```cpp
class Something
{
private:
    const int m_array[5];

public:
    Something() : m_array{ 1, 2, 3, 4, 5 } // initialise with uniform initialisation
    {
    }
};
```

### Initialising member variables that are classes

A member initialisation can be used to initialise members that are classes.

```cpp
#include <iostream>

class A
{
pubic:
    A(int x = 0) { std::cout << "A " << x << '\n'; }
};

class B
{
private:
    A m_a{};

public:
    B(int y) 
        : m_a{ y - 1 } // call A(int) comstructor to initialise member m_a
    {
        std::cout << "B " << y << '\n';
    }
};

int main()
{
    B b{ 5 };
    // prints 
    // A 4
    // B 5

    return 0;
}
```

### Formatting initialiser lists

There is a lot of flexibility as to how initialiser lists can be formatted.

Recommendations include:
- Everything on one line (good if initialiser list fits on same line as function name)
- Colon + list on indented line below (if cannot fit on one line)
- Each variable indented on a new line opening with comma separators (colon for first initialiser)

#### Initialiser list order

Variables in the initialiser list are not initialised in the order they are mentioned but the order in which they are declared in the class.
It is recommended that:
- You don't initialise member variables in such a way they are dependent on other member variables being initialised first (i.e. ensure propermember variables properly initialise independent of ordering).
- You initialise variables in the initialisr list in the same order they are declared in your class (not strictly necessary but may result in a warning if not).

## Non-static member initialisation

To avoid having to rewrite/update multiple constructors, it is possible to specify default values for private members as they are defined.
This works as long as the class member variables are normal (i.e. do not use the `static` keyword).

```cpp
class Rectangle
{
private:
    double m_length{ 1.0 }; // default value 1.0
    double m_width{ 1.0 }; // default value 1.0
};
```

Also called in-class member initialisation, non-static member initialisation provides default values to be used by member variables if constructors do not provide initialisation values for them.

However, it is still important to define constructors as they determine the type of objects that can be created.

```cpp
class Rectangle
{
private:
    double m_length{ 1.0 }; // default value 1.0
    double m_width{ 1.0 }; // default value 1.0

public:
    // no default constructor

    Rectangle(double length, double width)
        : m_length{ length }
        , m_width{ width}
    {
    }
};

int main()
{
    Rectangle x{}; // won't compile as no default constructor exists, even though members have default initialisation values provided via NSM initialisation

    return 0;
}
```

Since no default constructor is provided, we can't create Rectangle objects with no arguments.

If there is a default initialisation value and a value provided by the constructor, the constructor value takes precedence.

In general, favour non-static member initialisation to give default values for member variables.

## Delegating constructors

For every constructor we write, it is likely that we will want some similar functionality to be called every time.
We can avoid copy and pasting the same code into each constructor and have overlapping functionality by delegating (or chaining) constructors.

This allows constructors to call other constructors from the same class using the member initialiser list.

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    int m_id{};
    std::string m_name{};

public:
    Employee(int id=0, std::string_view name="")
        : m_id{ id }, m_name{ name }
    {
        std::cout << "Employee " << m_name << " created.\n";
    }

    // Use delegating constructor to minimise redundant code
    Employee(std::string_view name) : Employee{ 0, name }
    {
    }
};
```

Note that a constructor that delegatest to another constructor is not allowed to do any member initialisation itself: constructors can only delegate or initialise.

You should also be wary it is possible for constructors to delegate back to each other and form an infinite loop.
Avoid this by nsuring all constructors resolve to a non-delegating constructor.

Since constructors can either delegate or initialise, wWhen looking to perform setup code, it is usually best to create a normal member function that can be called by a constructor to do set up tasks.

```cpp
#include <iostream>

class Foo
{
private:
    const int m_value{ 0 };

    void setup() // setup function only usable by constructors
    {
        // code for tasks
        std::cout << "Setting things up... \n";
    }

public:
    Foo()
    {
        setup();
    }

    Foo(int value) : m_value{ value }
    {
        setup();
    }
};
```

Note that the setup function cannot initialise members, bind member references or set const values as it is not a constructor.
It also occurs after members have been created and initialised.

## Resetting a class object

We could rewrite our initial conditions to be assigned inside a function to be called if we desire, however this may be redndant code and there is no way for user-provided values to be re-obtained.

However, if the class is assignable (i.e. has an accessible assignment operator), we can create a new class object and overwrite the values in the object we want to reset.

```cpp
class Foo
{
private:
    int m_a{ 5 };
    int m_b{ 6 };

public:
    Foo()
    {
    }

    Foo(int a, int b) : m_a{ a }, m_b{ b }
    {
    }

    void reset()
    {
        *this = Foo{}; // creates new Foo object to overwrite implicit object by assignement
    }
};
```

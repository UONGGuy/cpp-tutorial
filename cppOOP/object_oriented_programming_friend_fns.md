# Object-Oriented Programming: Friend Functions

There may be situations where you have separate classes and functions that need to work together closely.
In these cases, it may not be beneficial to encapsulate certain details of the classes.

An example could be a data storage class that interacts with a data display class.
In this case, we could either:
- Have the display code use public functions of the storage class.
- Use friend classes and friend functions.

In the first case, downsides include defining such public member functions (which can clutter code) and the exposing of functions that you may not want anyone else to access.

The second case allows the display code to directly access all private members and functions of the storage class without letting others do so.
In this respect, it is the ideal solution.

Friending is commonly used when defining overloaded operators or when two or more classes need to work together in an intimate way.

## Friend functions

Friend functions are functions that can access a class' private members as though they were members of the class.

To declare a friend function, we simply use the `friend` keyword in front of the function prototype.
It doesn't matter if the friend function is declared under private or public.

```cpp
class Value
{
private:
    int m_value{};

public:
    Value(int value) : m_value{ value }
    {
    }

    friend bool isEqual(const Value& value1, const Value& value2);
};

bool isEqual(const Value& value1, const Value& value2)
{
    return (value1.m_value == value2.m_value);
}

int main()
{
    Value v1{ 5 };
    Value v2{ 6 };

    bool same{ isEqual(v1, v2) }; // returns false

    return 0;
}
```

`isEqual()` is a friend function of the Value class, taking two Value objects as its parameters.
Being a friend of the Value class, it can access the private members of all Value objects.
Note that `isEqual()` does not belong to the Value class so is not tied to a specific object and can be called without having to be tied to an object.
It simply has access to the private members of Value class objects.

It is possible for a function to be a friend of multiple classes, allowing access to each of their member variables.
Note that it may be necessary to forward declare a class prototype so the compiler is aware what the variables of the friend function mean before their defintions appear.

```cpp
#include <iostream>

class Humidity; // forward declare class so compiler aware when seen in friend function declaration

class Temperature
{
private:
    int m_temp{};

public:
    Temperature(int temp=0) : m_temp{ temp }
    {
    }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

class Humidity
{
private:
    int m_humidity{};

public:
    Humidity(int humidity=0) : m_humidity{ humidity }
    {
    }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity);
{
    std::cout << "The temperatre is " << temperature.m_temp << " and the humidity is " << humidity.m_humidity << '\n';
}

int main()
{
    Humidity hum{ 10 };
    Temperature temp{ 12 };

    printWeather(temp, humidity);

    return 0;
}
```

## Friend classes

It is possible to make an entire class a friend of another class, giving all the friend class' members access to private members of the other class.

```cpp
#include <iostream>

class Storage
{
private:
    int m_nValue{};
    double m_dValue{};

public:
    Storage(int nValue, double dValue) 
        : m_nValue{ nValue }, m_dValue{ dValue }
    {
    }

    freind class Display; // Display now a friend of Storage
};

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst)
        : m_displayIntFirst{ displayIntFirst }
    {
    }

    void displayItem(const Storage& storage
    {
        if (m_displayIntFirst)
        {
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        }
        else
        {
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
        }
    }
};

int main()
{
    Storage storage{ 5, 6.7 };
    Display display{ false };

    display.displayItemp(storage);

    return 0;
}
```

Since the Display class is a friend of the Storage class, any of Display's member that use a Storage class object can access its private members directly.

Although Display is a friend of Storage, it does not have direct access to the `*this` pointer of Storage objects.
Note also that Storage does not have access to Display's private members as it is not a friend of Display.
Both classes must declare the other as a friend to have access to each other's private members (friendship is only one-way).

Be careful when using friend functions and classes as they can violate encapsulation, potentially changing the details of the friend class.

## Friend member functions

It is possible to only make a single member function a friend rather than the entire class.
This is done similarly to making a normal function a frind except that the member function is written out in full (i.e. `friend className::fnName`).
Note that the defining/forward declaring of classes and member functions must be done in the right order so that the compiler is fully aware of all definitions.

```cpp
#include <iostream>

class Storage // forward declare so compiler aware

class Display // comes before storage as compiler needs to see full definitition to understand the member function that will be friend to Storage
{
private:
    bool m_displayIntFirst{};

public:
    Display (bool displayIntFirst) : m_displayIntFirst{ displayIntFirst }
    {
    }

void displayItem(const Storage& storage); // forward declare function to be friended so we can define components of a Storage object first
};

class Storage
{
private:
    int m_nValue{};
    double m_dValue{};

public:
    Storage(int nValue, double dValue)
        : m_nValue{ nValue }, m_dValue{ dValue }
    {
    }

    friend void Display::displayItem(const Storage& storage);
};

// define member function that will be friended now that full definition of Storage has been seen
void Display::displayItem(const Storage& storage)
{
    if (m_displayIntFirst)
        std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
    else
        std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}

int main()
{
    Storage storage(5, 6.7);
    Display display(false);

    display.displayItem(storage);

    return 0;
}
```

Although the ordering is a pain, it is only necessary if everything is being done in a single file.
A better solution is to put each class definition in a separate header file with member functions in corresponding .cpp files.
This way, all class definitions will be immediately visible in the .cpp files and no rearranging of classes or functions is necessary.



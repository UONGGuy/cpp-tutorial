# Object-Oriented Programming: the hidden "this" pointer

C++ keeps track of which object a member function is called on using a hidden pointer named "this".
The `this` pointer is a const pointer that always points to the object being operated on.
Because it is a function parameter, it doesn't add any memory usage to your class.

```cpp
class Simple
{
private:
    int m_id;

public:
    Simple(int id) : m_id{ id }
    {
    }

    void setID(int id) { m_id = id; }
    int getID() { return m_id; }
};

int main()
{
    Simple simple{ 1 }; // this = &simple inside the Simple constructor
    Simple simple2{ 2 }; // this = &simple2 inside the Simple constructor
    
    simple.setID(3); // this = &simple inside member function
    simple2.setID(4); // this = &simple2 inside member function

    return 0;
}
```

Although we only specify one arguent in member function `setID()`, the compiler actually converts it into a standard function call with an additional argument.

```cpp
simple.setID(2);

// compiler converts to
setID(&simple, 2);

// because function call is modified, member function definition must be changed too
void setID(int id) { m_id = id }

// compiler converts to
void setID(Simple* const this, int id) { this->m_id = id; }
// "this" pointer holds address of object simple

```

The `this` pointer is a hidden const pointer holding the address of the object the member function was called on.

## Explicitly referencing "this"

Explicitly referencing `this` can be useful if you have a constructor or member function where a parameter has the same name as a member variable.
Using `this` allows us to disambiguate the two.

```cpp
class Something
{
private:
    int data;

public:
    Something(int data)
    {
        this->data = data; // this->data is the member, data is the local parameter
    }
};
```

Although this is possible, it is still recommended to use the "m_" prefix for class member variables rather than using `this->` to disambiguate them with local variables.

## Chaining member functions

It can be useful to have a class member function return the object it was working with as a return value.
This allows many member functions to be chained together, allowing several member functions to be called on the same object.

```cpp
class Calc
{
private:
    int m_value{ 0 };

public:
    
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() { return m_value; }
};

int main()
{
    Calc calc{}; // initialise with value 0
    calc.add(5).sub(3).mult(4); // (((0 + 5) - 3) * 4)

    return 0;
}
```

Because the member functions return `*this` instead of being `void` functions, we can chain their usage.
This is often used when overloading operators for classes.

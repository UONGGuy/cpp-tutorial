# Overloading operators and function templates

There are instances where function instantiated using templates may not compile if the template tries to perform an action the type does not support (e.g. add integer value to a `std::string`).

To overcome this, we can define operators to allow instantiated functions to compile where normal they wouldn't due to the actual class types not supporting these operators.

```cpp
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents }
    {}

    friend std::ostream& operator<<(std::ostream& out, const Cents& c)
    {
        out << c.m_cents;
        return out;
    }
};

template <typename T>
const T& max(const T& x, const T& y)
{
    return (x < y) ? y : x;
}

int main()
{
    Cents nickel{ 5 };
    Cents dime{ 10 };

    Cents bigger = max(nickel, dime);
    std::cout << bigger << " is bigger\n";

    return 0;
}
```

C++ will create a template that looks like

```cpp
template<>
const Cents& max(const Cents& x, const Cents& y)
{
    return (x < y) ? y : x;
}
```

But it doesn't know how to evaluate `x < y` since we haven't taught it how to handle this for objects of our class.
To fix this, we can write an overload for `operator<` for any class we want to use `max` with.



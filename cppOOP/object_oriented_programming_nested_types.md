# Object-Oriented Programming: Nested types

It is possible to define types within classes as well as functions and data.
This is done by defining the type inside the class under the appropriate access specifier.

```cpp
#include <iostream>

class Fruit
{
public: // define type under publicto allow access from outside class
    enum FruiType // define an enum, not an enum class
    {
        apple,
        banana,
        cherry
    };

private:
    FruitType m_type{};
    int m_percentageEaten{ 0 };

public:
    Fruit(FruitType type) : m_type{ type }
    {}

    FruitType getType() const { return m_type; }
    int getPercentageEaten() const { return m_percentageEaten; }
};

int main()
{
    Fruit apple{ Fruit::apple }; // access FruitType via Fruit now

    if (apple.getType() == Fruit::apple)
        std::cout << "I am an apple\n";
    else
        std:::cout << "I am not an apple\n";

    return 0;
}
```

Classes essentially act as namespaces for nested types in a similar manner to enum classes.
In the example, the enum is qualified as `Fruit::` as `FruitType` is a normal enum that is part of the class.
If we defined a nested enum class instead of a normal enum, then we would have to access our enum via `Fruit::FruitType::`.

Enumerations are probably the most common type to be nested within classes but all other types are possible too.

Note that nested classes do not have any special access to the `this` pointer despite having the same access to member of the enclosing class.
Another limitation is that nested types cannot be forward declared though this is rarely a problem with the entire class definition (inc. nested type) generally #included where needed.

# Multiple inheritance

It is possible for a derived class to inherit members from more than one parent in C++.

To implement this, separate each base class with a comma when specifying.

```cpp
#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name;
    int m_age{};

public:
    Person(std::string_view name, int age)
        : m_name{ name }, m_age{ age }
    {}

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
};

class Employee
{
private:
    std::string m_employer;
    double m_wage{};

public:
    Employee(std::string_view employer, double wage)
        : m_employer{ employer }, m_wage{ wage }
    {}

    const std::string& getEmployer() const { return m_employer; }
    double getWage() const { return m_wage; }
};

class Teacher: public, Person, public Employee
{
private:
    int m_teachesGrade{};

public:
    Teacher(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade)
        : Person{ name, age }
        , Employee{ employer, wage }
        , m_teachesGrade{ teahesGrade }
    {}
};
```

## Mixins

Mixins are small classes that can be inherited from to add properties to a class.
As per their name, they are intended to be mixed into other classes and not instantiated on their own.

```cpp
#include <string>
#include <string_view>

struct Point2D
{
    int x;
    int y;
};

class Box // mixin Box class
{
public:
    void setTopLeft(Point2D point) { m_topLeft = point; }
    void setBottomRight(Point2D point) { m_bottomRight = point; }

private:
    Point2D m_topLeft{};
    Point2D m_bottomRight{};
};

class Label // mixin Label class
{
public:
    void setText(const std::string_view str) { m_text = str; }
    void setFontSize(int fontSize) { m_fontSize = fontSize; }

private:
    std::string m_text{};
    int m_fontSize{};
};

class Button: public Box, public Label 
{
};

int main()
{
    Button button{};
    button.Box::setTopLeft({ 1, 1 });
    button.Box::setBottomRight({ 10, 10 });
    button.Label::setText("Username: ");
    button.Label::setFontSize(6);

    return 0;
}
```

Mixins are often templatised for more general usage and typically do not use virtual functions.

It is possible for a derived class to inherit from a mixin base class using he derived class as a template type parameter (Curiously Recurring Template Pattern CRTP).

## Issues with multiple inheritance

Ambiguity can result if multiple base classes contain a function with the same name.
To get around this, you can explicitly specify the version to call by using the appropriate scope resolution operator.

If multiple inheritance from two classes with the same single base class occurs, then the so-called diamond problem can occur (named because of the shape of the inheritance tree diagram).

```cpp
class PoweredDevice
{
};

class Scanner: public PoweredDevice
{
};

class Printer: public PoweredDevice
{
};

class Copier: public Scanner, public Printer
{
};
```

There are ambiguity issues regarding how certain types of references should be resolved, whether there should be one or two copies of the most base class, etc.
Most issues can be addressed by using explicit scoping but the additional maintenance overhead required to deal with the greater complexity can cost a lot of time and effort.
There are ways to resolve the diamond problem using virtual base classes.

In general, multiple inheritance should be avoided where possible unless the alternatives lead to even more complexity.

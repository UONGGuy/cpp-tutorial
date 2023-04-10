# Inheritance

In C++, it is possible to create new objects that directly acquire the attribute and behaviours of other existing objects and can build upon them.
They do this through inheritance - an "is-a" relationship where the parent class (also called base class or superclass) has attributes which are passed down to the child class (also called derived class or subclass).

The child class inherits both behaviours (member functions) and properties (member variables) from the parent, subject to some access restrictions.
Since child classes are also fully-fledged classes themselves, the can also have their own members specific to themselves.

An example is if we create a class to represent a generic person and one to represent a baseball player - a category of person.

```cpp
#include <string>

class Person
{
public:
    std::string m_name{};
    int m_age{};

    Person(const std::string& name="", int age=0)
        : m_name{ name }, m_age{ age }
    {}

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
};

// publicly inheriting Person
class BaseballPlayer: public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage=0.0, int homeRuns=0)
        : m_battingAverage{ battingAverage }
        , m_homeRuns{ homeRuns }
    {}
};
```

Baseball players are also people so we want them to have the same attributes as a Person, but we don't want to rewrite duplicate code.
By adding `: public Person` after the class declaration for a Baseball player, we enable public inheritance our derived class now acquires the member functions and variables from Person.

It is possible to chain inheritance - i.e. a class can inherit from a derived class in the same manner.
Constructing inheritance chains allows for a set of reusable classes that are very general at the top of the hierarchy and become progressively more specific at each level.

## Order of construction of derived classes

When C++ constructs derived objects, it does so in phases.
It first constructs the base class at the top of the inheritance tree and then constructs each child class down until reaching the derived object itself.

Logically, this makes sense as the child class cannot exist without the parent.

This means the base constructor is called before the derived constructor can do anything substantial and the base portion of the object is set up before the derived constructor can do anything.
Because of this, we need to explicitly choose and call which base constructor is used when we set up the derived object to initialise the member variables inherited from the base class.
We do this by adding the base class constructor in the member initialiser list of the derived class.

```cpp
class Base
{
public:
    int m_id{};

    Base(int id=0) : m_id{ id }
    {}

    int getID() const return{ m_id; }
};

class Derived: public Base
{
public:
    double m_cost{};

    Derived(double cost=0.0, int id=0) 
        : Base{ id } // call Base(int) constructor with value id
    {}

    double getCost() const { return m_cost; }
};
```

It doesn't matter where in the Derived constructor member initialiser list the base constructor is called as it will always execute first.

When a derived class is destroyed, each destructor is called in the reverse order of construction.

## Access specifiers

Derived classes are unable to access the `private` members of base classes without using access functions or being friends.
They can, however, access all `public` members.
If we want members to be inheritable by classes but not accessible from the outside, we must list them under the `protected` specifier.

In general, it is better to use private members if you can and only use protected members when derived classes are planned and the cost to build and maintain an interface to private members only is too high.

## Types of inheritance

There are three types of inheritance named after the three access specifiers: public, protected, and private.
If not specified, C++ defaults to private inheritance.

In short, when members are inherited, the access specifier for an inherited member may be changed in the derived class depending on the type of inheritance specified (e.g. members that were public in the base class may become private in the derived class).

Things to bear in mind are that:
- A class can always access its own non-inherited members
- Whether a user outside the class can access a class member depends only on the access specifier assigned to the member in the class it currently belongs to.
- The derived class' ability to access inherited members depends on the access specifier inherited from the parent class.

### Public inheritance

This is the most commonly used type of inheritance.
Public inheritance means:
- Inherited public members &rarr; public members
- Inherited protected members &rarr; protected members
- Inherited private members &rarr; inaccessible

Public inheritance should be used unless you have a specific reason to do otherwise.

### Protected inheritance

This is the least common method of inheritance, used only in very particular cases.
Protected inheritance means:
- Inherited public members &rarr; protected members
- Inherited protected members &rarr; protected members
- Inherited private members &rarr; inaccessible

### Private inheritance

In private inheritance, all members from the parent class are inherited as private with inherited private members still inaccessible.
- Inherited public members &rarr; private members
- Inherited protected members &rarr; private members
- Inherited private members &rarr; inaccessible

This can be useful when the derived class has no obvious relationship to the base class but uses the base class for implementation internally.

## Summary

A base class can access its own members without restriction.
The public can only access its public members.
Derived classes can only access its protected and public members.

A derived class can access its own members without restriction.
It can access its base class' protected and public members, but not its private members.
The public can only access the derived class' public members.

The method of inheritance can change the access specifiers of members inherited to the derived class.

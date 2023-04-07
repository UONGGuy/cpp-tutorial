# Object-Oriented Programming: Header files

It is possible to define member function for a class outside of the class definition if desired.
As classes grow longer, it becomes more useful to be able to separate the class declaration and implementation portions as we don't concern ourselves with how the class is implemented, only how its public member functions interact.

We can write class member functions outside the class definition by prefixing them with the scope resolution operator (`::`) as if it were a function in a namespace.

```cpp
class Date
{
private:
    int m_year;
    int m_month;
    int m_day;

public:
    Date(int year, int month, int day);

    void SetDate(int year, int month, int day);

    // access functions usually one liners so left in definition
    int getYear() { return m_year; }
    int getMonth() { return m_month; }
    int getDay() { return m_day; }
};

// Date constructor
Date::Date(int year, int month, int day)
{
    SetDate(year, month, day);
}

// Date member function
void Date::SetDate(int year, int month, int day)
{
    m_month = month;
    m_day = day;
    m_year = year;
}
```

## In header files

Class definitions can be put in header files to allow reuse across multiple files or projects.
Traditionally, class definitions are put in header files (same name as class) and member functions defined outside the class are put in a .cpp file (same name as class).

Date.h:

```cpp
#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int m_year;
    int m_month;
    int m_day;

public:
    Date(int year, int month, int day);

    void SetDate(int year, int month, int day);

    // access functions usually one liners so left in definition
    int getYear() { return m_year; }
    int getMonth() { return m_month; }
    int getDay() { return m_day; }
};

#endif
```

Date.cpp:

```cpp
#include "Date.h"

// Date constructor
Date::Date(int year, int month, int day)
{
    SetDate(year, month, day);
}

// Date member function
void Date::SetDate(int year, int month, int day)
{
    m_month = month;
    m_day = day;
    m_year = year;
}
```

Any other header or code file that wants to use this class can now include the header and compile the member functions in too.

Although it is possible to put all member function definitions into the header file, it can clutter up the class definition and anything changed in the header code means all files including that header need to be recompiled.
This is as opposed to changing code in a .cpp file where only that .cpp file needs to be recompiled.

It is recommended that:
- For classes used only in one file that aren't intended for reuse, define directly in the single .cpp file used in
- For classes intended for reuse / multi-file usage, define them in a .h file with the same name as the class
- Define trivial member functions inside the class
- Default parameters for member functions should be declared in the class definitions (in the header file)
- Define non-trivial member functions in a .cpp file with the same name as the class


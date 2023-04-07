# Object-Oriented Programming: shallow and deep copying

## Shallow copying

This refers to memberwise copying done by C++ calling the default copy constructor and default assignment operators.
This is usually sufficient for simple classes that don't handle dynamically allocated memory.

When designing classes to handle dynamically allocated memory, shallow copying can cause issues as shallow copying a pointer only copies its address without allocating any memory or copying the contents being pointed to.
This can lead to issues where actions on the copy (such as going out of scope leading to memory deallocation) can affect the data of the original object.

To avoid this problem (arising from doing a shallow copy of pointer values), we can do a deep copy on any non-null pointers being copied.

## Deep copying

A deep copy allocates memory for the copy and then copies the actual value, providing a distinct memory for the memory to occupy not tied to the source.
This prevents actions done to the copy from affecting the source.
To do this, we need to write our own copy constructors and overload assignment operators.

```cpp
#include <cstring>
#include <cassert>

class MyString
{
private:
    char* m_data{};
    int m_length{};

public:
    // Default constructor
    MyString(const char* source="")
    {
        assert(source); // ensure non-null
        // String length + 1 char for terminator
        m_length = std::strlen(source) + 1;
        // Allocate buffer equal to length
        m_data new char[m_length];
        // Copy parameter string to buffer
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    // Copy constructor
    MyString(const MyString& source);

    // Destructor
    ~MyString() { delete[] m_data; }

    // Member function for deep copy
    void deepCopy(const MyString& source);
    
    // Assignement operator
    MyString& operator=(const MyString& source)
    {
        // self-assignment check
        if (this != source)
        {
            deepCopy(source);
        }
        return *this;
    }
};

void MyString::deepCopy(const MyString& source) // Assumes m_data initialised
{
    // Deallocate memory held by string first
    delete[] m_data;
    // m_length not a pointer, can shallow copy
    m_length = source.m_length;
    // m_data is a pointer so need to deep copy if non-null
    if (source.m_data)
    {
        // Allocate memory for copy
        m_data = new char[m_length];
        // Perform copy
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

// Copy constructor
MyString::MyString(const MyString& source)
{
    deepCopy(source);
}
```

The main differences between our assignment operator and our copy constructor are:
- We have added a self-assignment check
- We return `*this` to allow for operation chaining
- We need to explicitly deallocate values the string already holds to prevent memory leak when `m_data` is reallocated later (handled inside `deepCopy()`)

### A better solution

If possible, it is better to use classes in the standard library that are able to deal with dynamic memory (e.g. `std::string` and `std:vector`) so we do not have to handle memory management or overload the copy constructors and assignment operators to do proper deep copying.

# Object-Oriented Programming: Destructors

The dual to constructors, destructors are a special type of class member function that are executed when objects of said class are destroyed.

When an object goes out of scope normally, or if a dynamically allocated object is explicitly deleted, the class destructor (if it exists) is automatically called to do necessary clean-up before the object is removed from memory.

If your class object holds resources or requires maintenance before objct destruction, commands should be outlined in the destructor as it is typically the last thing to happen before the object is destroyed.
Resources refers to dynamically allocated memory, file or database handles, etc.
For fundamental type information, C++ is able to clean this up automatically by itself so a destructor may not be required for this.

Similar to constructors, destructors also have naming conventions:
- The destructor must have the same name as the class but preceeded by a tilde (~)
- The destructor cannot take any arguments
- The destructor has no return type
- Each class can only have a single destructor

Generally, destructors are not called explicitly since they are called automatically at obect destruction.
They can, however, safely call other member functions as the object isn't destroyed until after the destructor executes.

```cpp
#include <iostream>
#include <cstddef>
#include <cassert>

class IntArray
{
private:
    int* m_array{};
    int m_length

public:
    // constructor
    IntArray(int length)
    {
        assert(length > 0);

        m_array = new int[static_cast<std::size_t>(length)]{};
        m_length = length;
    }

    // destructor
    ~IntArray()
    {
        delete[] m_array; // deallocate array allocated earlier
    }

    void setValue(int index, int value) { m_array[index] = value; }

    int getValue(int index) { return m_array[index]; }

    int getLength() { return m_length; }
};

int main()
{
    IntArray ar( 10 ); // allocate 10 integers
    for (int count{ 0 }; count < ar.getLength(); ++count)
        ar.setValue(count, count+1)

    std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';

    return 0;
} // ar is destroyed here so ~IntArray() destructor function is called 
```

## RAII

Resource Acquisition Is Initialisation (RAII) is a programming technique that ties resource usage with the lifetime of objects with automatic duration (e.g. non-dynamically allocated objects).
In C++, RAII is done through classes with constructors and destructors where resources (such as memory, a file or database handle, etc) is typically acquired by the constructor for use when the object is alive.
The resource is then released in the destructor when the object is destroyed.

Using RAII prevents resource leaks as all resource-holding objects are automatically cleaned up.

Be wary that if you use `std::exit()`, your program will terminate and destructors will not be called.
It may be useful to write a log file or databased before exiting to ensure destructors do the necessary clean-up work.


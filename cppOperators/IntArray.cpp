/*  IntArray.cpp
 *
 *  Program to simulate an array using a class
 *
 */

#include <iostream>
#include <cassert>

class IntArray
{
private:
    int m_length{ 0 };
    int *m_array{ nullptr };

public:
    // Default constructor; No implicit conversions
    explicit IntArray(int length=0) : m_length{ length }
    {
        assert(m_length > 0 && "Array has invalid/no length");
        m_array = new int[m_length]{};
    }

    // Copy constructor
    IntArray(const IntArray& source)
    {
        deepCopy(source);
    }

    // Function for deep copy
    void deepCopy(const IntArray& source);

    // Destructor
    ~IntArray()
    {
        delete[] m_array;
    }

    friend std::ostream& operator<<(std::ostream& out, const IntArray& array)
    {
        for (int i{ 0 }; i < array.m_length; ++i)
        {
            out << array.m_array[i] << ' ';
        }
        return out;
    }

    int& operator[](const int i)
    {
        assert(i >= 0 && i < m_length && "Index out-of-bounds");
        return m_array[i];
    }

    IntArray& operator=(const IntArray& source)
    {
        if (this == &source) // self-assignment check
        {
            return *this;
        }
        else
        {
            // Deallocate original memory
            delete[] m_array;
            // Deep copy
            deepCopy(source);
            return *this;
        }
    }
};

void IntArray::deepCopy(const IntArray& source)
{
    m_length = source.m_length;
    m_array = new int[m_length]{};
    for (int i{ 0 }; i < source.m_length; ++i)
    {
        m_array[i] = source.m_array[i];
    }
};

IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;
    
    return a;
}

int main()
{
    IntArray a{ fillArray() };
    std::cout << a << '\n';

    auto& ref{ a };
    a = ref;

    IntArray b(1);
    b = a;

    std::cout << b << '\n';

    return 0;
}

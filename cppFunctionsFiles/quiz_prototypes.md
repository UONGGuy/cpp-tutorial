# Chapter 12 Quiz prototypes

## A function named max() taking two doubles and returning the larger

```cpp
double max(double a, double b)
{
    return a > b ? a : b;
}
```

## A function named swap that swaps two integers

```cpp
void swap(int& a, int& b)
{
    int temp{ a };
    
    a = b;
    b = temp;
}
```

## A function named getLargestElement() taking a dynamically allocated array of integers and returning the largest number to be changed if required

```cpp
#include <algorithm>

int& getLargestElement(int* arr, int length))
{
    int maxValue{ arr[0] };
    int maxIndex{ 0 }
    
    for (int i{ 0 }; i < length; ++i)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
            maxIndex = i;
        }
    }

    return arr[maxIndex];
}


/*  valueFinder.cpp

    Function to search for given value, return a pointer to first 
    element with that value, or end pointer if no element found.

    In practice, use std::find() from the <algorithm> header
*/

#include <iostream>
#include <iterator>

int* findValue(int* start, int* end, int value)
{
    for (int* ptr{ start }; ptr != end; ++ptr)
    {
        if (value == *(ptr))
        {
            return ptr;
        }
    }
    return end;
}

int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };

    // Search for first element with value 20
    int* found{ findValue(std::begin(arr), std::end(arr), 20) };

    // If element with value 20 found, print it
    if (found != std::end(arr))
    {
        std::cout << *found << '\n';
    }
    
    return 0;
}

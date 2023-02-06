/*  BubbleSort2.cpp

    Program to apply bubble sort algorithm array:

    { 6, 3, 2, 9, 7, 1, 5, 4, 8 }

    Unoptimised bubble sort follows the following steps:
    1. Compare element 0 with element 1. If element 0 is larger,
    swap with element 1.
    2. Repeat with each subsequent pair of elements until the end
    of the array.
    3. Repeat steps 1 and 2 again until array is sorted.

    Add following optimisations:
    - Don't re-check sorted elements (elements at array end)
    - If no swaps made in iteration, terminate loop early
*/

#include <iostream>
#include <iterator>
#include <utility>

int main()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int array_length{ static_cast<int>(std::size(array)) };

    for (int sort_number{ 1 }; sort_number <= array_length; ++sort_number)
    {
        int swap_count{ 0 }; // could use a bool instead
        
        for (int indexA{ 0 }; indexA < array_length - sort_number; ++indexA)
        {
            int indexB{ indexA + 1 };

            if (array[indexA] > array[indexB])
            {
                std::swap(array[indexA], array[indexB]);
                ++swap_count;
            }
        }

        if (swap_count == 0)
        {
            std::cout << "Early termination on iteration " << sort_number << std::endl;
            break;
        }
    }
    
    for (int i{ 0 }; i < array_length; ++i)
        std::cout << array[i] << ' ';

    std::cout << "\n";

    return 0;
}

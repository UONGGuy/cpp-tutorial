/*  PrintArray.cpp

    Program to print an array of elements:
    { 4, 6, 7, 3, 8, 2, 1, 9, 5 }

*/

#include <iostream>

int main()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    int array_length{ sizeof(array) / sizeof(array[0]) };
    
    for (int i{ 0 }; i < array_length; ++i)
    {
        std::cout << array[i] << std::endl;
    }

    return 0;
}

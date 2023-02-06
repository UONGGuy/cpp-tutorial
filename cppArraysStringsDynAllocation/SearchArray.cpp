/*  SearchArray.cpp

    Program to ask the user to enter a number from 1 - 9, print the
    array and then print the index of the number input.

    Array: { 4, 6, 7, 3, 8, 2, 1, 9, 5 }

*/

#include <iostream>
#include <array>
#include <algorithm> // for std::binary_search

int getInput()
{
    int user_value{};
    bool check{ false };

    do
    {
    std::cout << "Please select a number from 1 - 9: ";
    std::cin >> user_value;

    std::array<int, 9> valid_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    if (std::binary_search(valid_values.begin(), valid_values.end(), user_value)) // could also use a loop to check this
    {
        check = true;
    }

    else
    {
        std::cin.clear(); // reset any error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any char in input buffer
    }

    }
    while (check == false); // while (user_value < 1 || user_value > 9)

    return user_value;
}

int main()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    int array_length{ sizeof(array) / sizeof(array[0]) };

    int user_value{ getInput() };
    int user_index{};
    
    for (int i{ 0 }; i < array_length; ++i)
    {
        std::cout << array[i] << std::endl;
        
        if (user_value == array[i])
            user_index = i;
    }

    std::cout << "The number " << user_value << " has index " << user_index << std::endl;

    return 0;
}

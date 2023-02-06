/*  nameSearch.cpp

    Program to check if name entered by user is in array using a 
    for-each loop.

    Array: Alex, Betty, Caroline, Dave, Emily, Fred, Greg, Holly
*/

#include <iostream>
#include <string>
#include <string_view>

int main()
{
    constexpr std::string_view database[]{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };

    std::string check{};
    std::cout << "Enter a name: ";
    std::getline(std::cin, check);

    bool found{ false };

    for (auto name : database)
    {
        if (check == name)
            found = true;
    }

    if (found)
        std::cout << check << " was found.\n";
    else
        std::cout << check << " was not found.\n";

    return 0;
}

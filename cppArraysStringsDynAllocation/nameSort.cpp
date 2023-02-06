/*  nameSort.cpp

    Program to:
    - Ask how many names are to be entered
    - Dynamically allocate a std::string array
    - Asks the user to enter each name
    - Sorts names using std::sort
    - Prints sorted list of names

    Note: std::string supports string comparisons through the < and > 
    operators.
*/

#include <iostream>
#include <string>
#include <algorithm>

void getNames(std::string* nameArray, int numNames)
{

    for (int count{ 0 }; count < numNames; ++count)
    {
        std::string name{};
        std::cout << "Enter name #" << count + 1 << ": ";
        std::getline(std::cin >> std::ws, nameArray[count]); 
        // std::ws to remove leading whitespae from input stream
    }
}

void printSorted(std::string* nameArray, int numNames)
{
    std::sort(nameArray, nameArray + numNames);

    std::cout << "Here is your sorted list:\n";

    for (int count{ 0 }; count < numNames; ++count)
    {
        std::cout << "Name #1: " << nameArray[count] << '\n';
    }
}

int main()
{
    int numNames{};
    std::cout << "How many names would you like to enter? ";
    std::cin >> numNames;

    auto* nameArray{ new std::string[numNames]{} };

    getNames(nameArray, numNames);

    printSorted(nameArray, numNames);

    delete[] nameArray; // Remember this important step!!

    return 0;
}

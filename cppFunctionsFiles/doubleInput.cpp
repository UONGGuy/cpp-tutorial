#include <iostream>

/*  Program to print double the value of input integer. 

    INPUT: int x

    OUTPUT: (2 * x)

*/

// Function to prompt user for integer input and return its value
int getUserValue()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

int main()
{
    int num { getUserValue() };
    
    std::cout << num << " doubled is " << 2 * num << std::endl;

    return 0;
}

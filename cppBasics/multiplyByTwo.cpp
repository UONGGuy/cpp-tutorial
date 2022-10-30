#include <iostream>

/*  Program to multiply input integer by 2 and return output.
    
    INPUT: int x

    OUTPUT: int result = (2 * x)
*/

int main()
{
    int x{}; // Input variable

    std::cout << "Enter an integer: "; // Prompt
    std::cin >> x; // Assign input variable to x

    std::cout << "Double that number is: " << 2 * x << std::endl;
    // Print 2 * input

    return 0;
}

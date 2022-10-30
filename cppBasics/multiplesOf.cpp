#include <iostream>

/*  Program to print the multiples of an input integer.

    INPUT: int x
    
    OUTPUT: (2 * x), (3 * x)
*/

int main()
{
    int num{}; // Variable for input integer

    std::cout << "Enter an integer: "; // Prompt
    std::cin >> num; // Assign integer to num

    std:: cout << "Double " << num << " is: " << num * 2 << std::endl;
    std:: cout << "Triple " << num << " is: " << num * 3 << std::endl;

    return 0;
}

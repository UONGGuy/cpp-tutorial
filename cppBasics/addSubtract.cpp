#include <iostream>

/*  Program to find the sum and difference of two input integers.

    INPUTS: int x1, x2
    
    OUTPUTS: (x1 + x2), (x1 - x2)
*/

int main()
{
    int num_1{}, num_2{}; // Variables for input integers

    std::cout << "Enter an integer: " << std::endl; // Prompt
    std:: cin >> num_1; // Assign first input
    std::cout << "Enter another integer: " << std::endl; 
    std:: cin >> num_2; // Assign second input

    std::cout << num_1 << " + " << num_2 << " is " << num_1 + num_2
    << std::endl; // Return sum of inputs
    std::cout << num_1 << " - " << num_2 << " is " << num_1 - num_2
    << std::endl;  // Return difference of inputs

    return 0;
}

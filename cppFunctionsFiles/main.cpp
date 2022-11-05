/*  Program to read in two separate integers, sum them and print the 
    answer.

    INPUT: int x, y

    OUTPUT: print(x + y)

*/

#include <iostream>

int readNumber();
void writeAnswer(int x);

int main()
{
    // get inputs from user
    int x { readNumber() };
    int y { readNumber() };

    // sum answer as new variable
    int z { x + y };

    // print answer
    writeAnswer(z);

    return 0;
}

int readNumber()
{
    int x {};
    std::cout << "Choose integer: ";
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The sum of the above integers is " << x << std::endl;
}

/*  Program to read in two separate integers, sum them and print the 
    answer using header and separate functions file.

    INPUT: int x, y

    OUTPUT: print(x + y)

*/

#include "io.h"
#include <iostream>

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

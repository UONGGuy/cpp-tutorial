/*  swapInt.cpp

    Function to swap the value of two integer variables.
*/

#include <iostream>

// Use reference params so values of args can be modified
// Else will just make copies of arg variabales
void swapInt(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
}

int main()
{
    int a{ 5 };
    int b{ 12 };

    std:: cout << "a = " << a << ", b = " << b << '\n'; 

    swapInt(a, b);

    std::cout << "Swapping!\na = " << a << ", b = " << b << '\n';

    return 0;
}

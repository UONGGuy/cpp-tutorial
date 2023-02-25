/*  factorial.cpp

    Progam to calculate the factorial of an input value.

*/

#include <iostream>

int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int getInteger()
{
    while (true)
    {
        std::cout << "Enter an integer: ";
        int value{};
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return value;
    }
}

int main()
{
    int n{ getInteger() };

    std::cout << n << "! = " << factorial(n) << '\n';

    return 0;
}

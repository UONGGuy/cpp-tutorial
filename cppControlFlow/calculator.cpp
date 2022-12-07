/*  calculator.cpp

    Program to calculate the result of an operation applied to two
    integers (user inputs).

*/

#include <iostream>

int calculate(int x, int y, char operate)
{
    switch(operate)
    {
        case '+':
        {
            return (x + y);
        }
        case '-':
        {
            return (x - y);
        }
        case '*':
        {
            return (x * y);
        }
        case '/':
        {
            return (x / y);
        }
        case '%':
        {
            return (x % y);
        }
        default:
        {
            std::cerr << "calculate(): Unhandled case\n";
            return 0;
        }
    }
}

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y {};
    std::cin >> y;

    std::cout << "Enter an operation (+, -, *, /, %): ";
    char operate {};
    std::cin >> operate;

    int result { calculate(x, y, operate) };
    std::cout << x << operate << y << " is " << result << std::endl;

    return 0;
}

/*  calculator.cpp

    Program to take two float input and an operation symbol, returning the answer if valid, nothing if symbol invalid.

    INPUT: float x, y; char operation;

    OUTPUT: (x operation y) if operation valid, else nothing

*/

#include<iostream>

double getDouble();
char getOperator();
void printResult(double x, double y, char op);

int main()
{
    /*
    getInput -> double x
    getInput -> double y
    getOperator -> -1, 0, 1, 2, 3
    if -1 -> return nothing
    if 0, 1, 2, 3 -> corresponding operation -> return value
    */
    double x { getDouble() };
    double y { getDouble() };
    char op { getOperator() };

    printResult(x, y, op);
    
    return 0;
}

double getDouble()
{
    std::cout << "Enter a double value: ";
    double x {};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter an operation (+, -, *, /): ";
    char op {};
    std::cin >> op;
    
    return op;
}

void printResult(double x, double y, char op)
{
    if (op == '+')
    {
        std::cout << x << " + " << y << " is " << x + y << std::endl;
    }
    if (op == '-')
    {
        std::cout << x << " - " << y << " is " << x - y << std::endl;
    }
    if (op == '*')
    {
        std::cout << x << " * " << y << " is " << x * y << std::endl;
    }
    if (op == '/')
    {
        std::cout << x << " / " << y << " is " << x / y << std::endl;
    }
}

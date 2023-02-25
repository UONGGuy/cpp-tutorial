/*  calculator.cpp

    Program to provide the basic functions of a calculator using 
    function pointers.

    - Ask user for 2 int inputs and a maths operation (ensure valid)
    - Write functions add(), subtract(), multiply(), divide() that take
      two int params and return an int
    - Create type alias ArithmeticFunction for pointer to a function 
      that takes two int param and returns and in. Use std::function.
    - Write function getArithmeticFunction() taking operator char and 
      returning appropriate function as function pointer
    - Modify main() to call getArithmeticFunction() and return call
      value from function with inputs and print results.
*/

#include <iostream>
#include <functional>

int getInteger()
{
    while(true)
    {
        int user_int{};
        std::cout << "Enter an integer: ";
        std::cin >> user_int;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return user_int;
    }
}

char getOperation()
{
    while(true)
    {
        char operation{};
        std::cout << "Enter an operation (+, -, *, /): ";
        std::cin >> operation;

        if (std::cin.fail() or (operation != '+' and operation != '-' and operation != '*' and operation != '/'))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return operation;
    }

}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    return x / y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char operation)
{
    switch(operation)
    {
        case '+':       return &add;
        case '-':       return &subtract;
        case '*':       return &multiply;
        case '/':       return &divide;

        default:
        {
            std::cout << "Arithmetic Funtion error\n";
            return nullptr;
        }
    }
}

int main()
{
    int x{ getInteger() };
    char operation{ getOperation() };
    int y{ getInteger() };

    ArithmeticFunction fcn{ getArithmeticFunction(operation) };

    std::cout << x << operation << y << "=" << fcn(x, y) << '\n';
    
    return 0;
}

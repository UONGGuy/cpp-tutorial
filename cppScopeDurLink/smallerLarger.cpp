#include <iostream>

int getInteger();

int main()
{
    std::cout << "Enter an integer: ";
    int x{ getInteger() };
    
    std::cout << "Enter a larger integer: ";
    int y{ getInteger() };
    
    if (x > y)
    {
        std::cout << "Swapping the values\n";
        int z { y }; // temporary variable for switch
        y = x;
        x = z;
    } // z destroyed here
    
    std::cout << "The smaller value is " << x << std::endl;
    std::cout << "The larger value is " << y << std::endl;

    return 0;
} // x and y destroyed here

int getInteger()
{
    int x {};
    std::cin >> x;
    return x;
}

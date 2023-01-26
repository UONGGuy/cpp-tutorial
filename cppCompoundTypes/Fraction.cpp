/*  Fraction.cpp

    Program to read in 2 fractions and return their product.

*/

#include <iostream>

struct Fraction
{
    int numerator{ 0 };
    int denominator{ 1 };
};

Fraction getFraction()
{
    Fraction fraction{};
    std::cout << "Enter a value for the numerator: ";
    std::cin >> fraction.numerator;
    std::cout << "Enter a value for the denominator: ";
    std::cin >> fraction.denominator;
    std::cout << std::endl;

    return fraction;
}

void multiplyFractions(Fraction A, Fraction B)
{
    std::cout << "Your fractions multiplied together: " << A.numerator * B.numerator << "/" << A.denominator * B.denominator << "\n";
}

int main()
{
    Fraction frac1{ getFraction() };
    Fraction frac2{ getFraction() };
    
    multiplyFractions(frac1, frac2);

    return 0;
}

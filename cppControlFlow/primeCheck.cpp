/*  primeCheck.cpp

    Program to check if given values are or are not prime.

*/

#include <iostream>
#include <cassert>
#include <math.h>

bool isPrime(int x)
{
    int factors { 1 }; // x is a factor of x

    // 0 and 1 are not prime
    if (x == 0 or x == 1)
        return false;
    // Check for other factors
    // Only need to check factors up to sqrt(x)
    for (int i { 1 }; i <= static_cast<int>(sqrt(x)); ++i)
    {
        // If x has any additional factors
        if (x % i == 0)
            ++factors;
        // If x has more than 2 factors (i.e. more than 1 and itself), not prime
        if (factors > 2)
            return false;
    }

    // If x has only 2 factors, prime
    return true;
}

int main()
{
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert(isPrime(2));
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";

    return 0;
}

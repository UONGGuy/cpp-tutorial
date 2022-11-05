/*  Program to test directives.

    Comment in/out #define TEST_1 and #define TEST_2 to see what happens.

*/

#include <iostream>
#define TEST_1 5
#define TEST_2 "contents of TEST_2"

int main()
{
// If TEST_1 is defined
#ifdef TEST_1
    std::cout << "Test 1 is defined. Content: " << TEST_1 << "\n";
#endif
// If TEST_1 not defined
#ifndef TEST_1
    std::cout << "Test 1 not defined. \n";
#endif

// If TEST_2 is defined
#ifdef TEST_2
    std::cout << "Test 2 is defined. Content: " << TEST_2 << "\n";
#endif
// If TEST_2 not defined
#ifndef TEST_2
    std::cout << "Test 2 not defined. \n";
#endif

    return 0;
}

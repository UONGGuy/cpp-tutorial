/*  helloWorld_cstyle.cpp

    Program to print "Hello world!" from a C-style string, char by char.

    - Use pointer to step through each char of string and print char
*/

#include <iostream>

int main()
{
    const char* phrase{ "Hello world!" };
    
    
    for (auto* ptr{ phrase }; *ptr != '\0'; ++ptr)
        std::cout << *ptr << '\n';

    return 0;
}

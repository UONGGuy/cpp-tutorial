/*  lowerTriangular.cpp

    Program to print the following:

            1
          2 1
        3 2 1
      4 3 2 1
    5 4 3 2 1

*/

#include <iostream>

int main()
{
    int count { 1 };

    while (count <= 5)
    {
        int spaces { 5 - count };
        
        while (spaces > 0)
        {
            std::cout << "  ";
            --spaces;
        }

        int numbers { count };
        
        while (numbers > 0)
        {
            std::cout << numbers << ' ' ;
            --numbers;
        }

        // could use an if statement instead of 2 loops
        /*  int spaces { 5 } 
            while (spaces >= 1)
            {
                if (spaces <= count)
                    std::cout << spaces << ' ';
                else
                    std::cout << "  ";
                --inner;
            } 
        */

        std::cout << '\n';
        ++count;
    }

    return 0;
}

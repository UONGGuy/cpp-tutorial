/*  AnimalLegs.cpp

    Program to print the number of legs of an animal from database.

*/

#include <iostream>

namespace Animal
{
    enum Genus
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,

        number_of_animals,
    };
}

int main()
{
    int legCount[Animal::number_of_animals]{ 2, 4, 4, 4, 2, 0 };

    std::cout << "An elephant has " << legCount[Animal::elephant] << " legs.\n";

    return 0;    
}

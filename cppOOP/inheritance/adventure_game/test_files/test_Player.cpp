#include "../Creatures.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your name: ";
    std::string name{};
    std::cin >> name;

    Player player1{ name };

    std::cout << "Welcome, " << player1.getName() << '\n';
    std::cout << "You have " << player1.getHp() << " health and are carrying " << player1.getGold() << " gold.\n";

    return 0;
}

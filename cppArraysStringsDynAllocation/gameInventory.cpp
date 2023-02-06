/*  gameInventory.cpp

    Program to simulate holding 3 types of items in a game.

    - Create an enum to identify types of items
    - Create a std::array to store number of items carried
    - Player starts with 2 health potions, 5 torches, 10 arrows
    - Write function countTotalItems() to return total items held
    - Print countTotalItems() output in main and number of torches
*/

#include <iostream>
#include <array>

namespace Objects
{
    enum Items
    {
        health_pot,
        torch,
        arrow,
        total_items,
    };
}

int countTotalItems(const std::array<int, Objects::Items::total_items>& inventory)
{
    int total{ 0 };
    for (int item_qty : inventory)
        total = total + item_qty;
    return total;
}

int main()
{
    std::array inventory{ 2, 5, 10 };

    std::cout << "PLayer has " << countTotalItems(inventory) << " total items.\n";

    std::cout << "Player has " << inventory[Objects::Items::torch] << " torches.\n";

    return 0;
}

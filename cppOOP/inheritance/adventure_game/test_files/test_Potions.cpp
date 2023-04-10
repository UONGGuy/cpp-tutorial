#include "../Creatures.h"
#include "../Items.h"
#include <iostream>

int main()
{
    Potion potion{ Potion::Type::health, Potion::Size::small };
    std::cout << "Potion hp and dmg: " << potion.getHP() << ", " << potion.getDMG() << '\n';

    Player player{ "name" };
    std::cout << "Player hp and dmg: " << player.getHp() << ", " << player.getDmgPerHit() << '\n';

    std::cout << "Drink pot\n";
    player.drinkPotion(potion);
    std::cout << "Player hp and dmg: " << player.getHp() << ", " << player.getDmgPerHit() << '\n';

    return 0;
}

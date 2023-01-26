/*  MyMonsters.cpp

    Program to print out my monsters and their health.

*/

#include <iostream>
#include <string_view>

enum class MonsterType
{
    ogre,
    dragon,
    orc,
    giant_spider,
    slime,
};

struct Monster
{
    MonsterType type{};
    std::string_view name{};
    int hp{0};
};

constexpr std::string_view getMonsterType(MonsterType type)
{
    switch(type)
    {
        case MonsterType::ogre:
            return "ogre";
        case MonsterType::dragon:
            return "dragon";
        case MonsterType::orc:
            return "giant spider";
        case MonsterType::slime:
            return "slime";

        default:
            return "???";
    }
}

void printMonster(const Monster& monster)
{
    std::cout << "This " << getMonsterType(monster.type);
    std::cout << " is named " << monster.name;
    std::cout << " and has " << monster.hp << " health.\n";
}

int main()
{
    Monster monster1{ MonsterType::ogre, "Torg", 145 };
    printMonster(monster1);

    Monster monster2{ MonsterType::slime, "Blurp", 23 };
    printMonster(monster2);

    return 0;
}

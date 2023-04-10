#include "Creatures.h"
#include "Items.h"
#include "Random_MT.h"
#include <array>

/*
 * Creatures class
 */

void Creature::reduceHealth(int dmg)
{
    hp -= dmg;
}

bool Creature::isDead() const
{
    if (hp <= 0)
        return true;

    return false;
}

void Creature::addGold(int loot)
{
    gold += loot;
}

/*
 * Player class
 */

void Player::levelUp()
{
    ++level;
    ++dmgPerHit;
}

void Player::drinkPotion(Potion& potion)
{
    hp += potion.getHP();
    dmgPerHit += potion.getDMG();
}

bool Player::hasWon() const
{
    if (level >= player_max_level)
        return true;

    return false;
}

/*
 * Monster class
 */

const Creature& Monster::getDefaultCreature(Type type)
{
    static const std::array<Creature, static_cast<std::size_t>(Type::max_monster_types)> monsterData{
        { { "dragon", 'D', 20, 4, 100 },
          { "orc", 'o', 4, 2, 25 },
          { "slime", 's', 1, 1, 10 } }
    };

    return monsterData.at(static_cast<std::size_t>(type));
}

Monster Monster::getRandomMonster()
{
    int number{ RandomMT::getRandomInt(0, static_cast<Type>(Type::max_monster_types - 1)) };

    return Monster{ static_cast<Type>(number) };
}

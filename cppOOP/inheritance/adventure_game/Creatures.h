#ifndef CREATURES_H
#define CREATURES_H

#include "Items.h"
#include <string>
#include <string_view>
#include <type_traits>

class Creature 
{
protected:
    std::string name{};
    char symbol{};
    int hp{};
    int dmgPerHit{};
    int gold{};

public:
    Creature(std::string_view name, char symbol, int hp, int dmgPerHit, int gold)
        : name{ name }
        , symbol{ symbol }
        , hp{ hp }
        , dmgPerHit{ dmgPerHit }
        , gold{ gold }
    {}

    // getters
    std::string_view getName() const { return name; }
    char getSymbol() const { return symbol; }
    int getHp() const { return hp; }
    int getDmgPerHit() const { return dmgPerHit; }
    int getGold() const { return gold; }

    // add functions
    void reduceHealth(int dmg);
    bool isDead() const;
    void addGold(int loot);
};
    
class Player: public Creature
{
private:
    int level{ 1 };
    static constexpr int player_max_level{ 20 };

public:
    Player(std::string_view username)
        : Creature(username, '@', 10, 1, 0)
    {}

    //getters
    int getLevel() const { return level; }

    // add functions
    void levelUp();
    void drinkPotion(Potion& potion);
    bool hasWon() const;
};

class Monster: public Creature
{
public:
    enum Type 
    {
        dragon,
        orc,
        slime,

        max_monster_types
    };

private:
    // lookup table for monster stats
    static const Creature& getDefaultCreature(Type type);

public:
    Monster(Type type)
        : Creature{ getDefaultCreature(type) }
    {}

    // random monster generator
    static Monster getRandomMonster();

};

#endif
